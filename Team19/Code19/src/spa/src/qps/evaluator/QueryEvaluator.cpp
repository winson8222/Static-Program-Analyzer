#include "QueryEvaluator.h"
#include "qps/evaluator/ResultTable.h"
#include <variant>
#include "strategies/WithStrategy.h"

using namespace std;

// ai-gen start(copilot, 2, e)
// prompt: used copilot
// Constructor for QueryEvaluator class.
// Initializes the strategy and entity factories and sets up the PKB reader manager and parsing result.
QueryEvaluator::QueryEvaluator(std::shared_ptr<PKBReaderManager> pkbReaderManager, ParsingResult& parsingResult)
    : pkbReaderManager(pkbReaderManager), parsingResult(parsingResult) {
    initializeStrategyFactory();
    initializeEntityFactory();
}

// Adds a new query evaluation strategy to the list of strategies.
void QueryEvaluator::addStrategy(std::unique_ptr<QueryEvaluationStrategy> strategy) {
    strategies.push_back(std::move(strategy));
}

void QueryEvaluator::constructEntryString(std::string& entry, std::string& synonym, std::unordered_map<std::string, std::string>& map) {
    // i check if synonym is a AttrRef
    if (ParsingResult::isAttrRef(synonym)) {
        string synonymSyn = ParsingResult::getSynFromAttrRef(synonym);
        std::string ref = map.at(synonymSyn);
        string convertedAttr = convertToAttr(synonym, ref);
        entry.empty() ? entry = convertedAttr : entry += " " + convertedAttr;
        return;
    }
	entry.empty() ? entry = map.at(synonym) : entry += " " + map.at(synonym);
}

void QueryEvaluator::addEntriesToFinalWithResultOnly(std::unordered_set<std::string>& finalSet, std::vector<std::string> requiredSynonyms) {
	for (auto row : result->getRows()) {
		std::string toAdd;
		for (auto requiredSynonym : requiredSynonyms) {
			constructEntryString(toAdd, requiredSynonym, row);
		}
		finalSet.insert(toAdd);
	}
}

void QueryEvaluator::addEntriesToFinalWithCrossJoinAndResult(std::unordered_set<std::string>& finalSet, std::vector<std::string> requiredSynonyms, std::unordered_map<std::string, std::string> crossJoinMap) {
	for (auto row: result->getRows()) {
		std::string toAdd;
		for (auto requiredSynonym : requiredSynonyms) {
            string requiredSynonymForChecking;
            if (ParsingResult::isAttrRef(requiredSynonym)) {
                requiredSynonymForChecking = ParsingResult::getSynFromAttrRef(requiredSynonym);
            } else {
                requiredSynonymForChecking = requiredSynonym;
            }

			if (crossJoinMap.find(requiredSynonymForChecking) != crossJoinMap.end()) {
				constructEntryString(toAdd, requiredSynonym, crossJoinMap);
			} else {
				constructEntryString(toAdd, requiredSynonym, row);
			}
		}
		finalSet.insert(toAdd);
	}
}
void QueryEvaluator::addEntriesToFinalWithOnlyCrossJoin(std::unordered_set<std::string>& finalSet, std::vector<std::string> requiredSynonyms, std::unordered_map<std::string, std::string> crossJoinMap) {
	std::string toAdd;
	for (auto requiredSynonym : requiredSynonyms) {
		constructEntryString(toAdd, requiredSynonym, crossJoinMap);
	}
	finalSet.insert(toAdd);
}

std::vector<std::unordered_map<std::string, std::string>> QueryEvaluator::getCrossJoinMapList(
		std::vector<std::string> requiredSynonyms) {
	std::vector<std::unordered_map<std::string, std::string>> crossJoinMapList;
	for (auto requiredSynonym: requiredSynonyms) {
		if (result->hasColumn(requiredSynonym)) continue;
		std::string requiredType = parsingResult.getRequiredSynonymType(requiredSynonym);
		unordered_set<string> currentResult = getAllEntities(requiredType);
		if (crossJoinMapList.empty()) {
			for (auto entity : currentResult) {
				std::unordered_map<std::string, std::string> tempMap;
				tempMap[requiredSynonym] = entity;
				crossJoinMapList.push_back(tempMap);
			}
			continue;
		}
		std::vector<std::unordered_map<std::string, std::string>> newCrossJoinMapList;
		for (auto entity : currentResult) {
			for (auto map : crossJoinMapList) {
				std::unordered_map<std::string, std::string> tempMap = map;
				tempMap[requiredSynonym] = entity;
				newCrossJoinMapList.push_back(tempMap);
			}
		}
		crossJoinMapList = newCrossJoinMapList;
	}
	return crossJoinMapList;
}

std::vector<std::string> QueryEvaluator::removeAllAttrRefs(const std::vector<std::string>& requiredSynonyms) {
    std::vector<std::string> processedSynonyms;
    std::unordered_set<std::string> seen; // To ensure uniqueness without duplicates

    for (const string& synonym : requiredSynonyms) {
        std::string processedSynonym = synonym;
        if (ParsingResult::isAttrRef(synonym)) {
            processedSynonym = ParsingResult::getSynFromAttrRef(synonym);
        }
        // Insert into set to ensure uniqueness
        if (seen.insert(processedSynonym).second) {
            processedSynonyms.push_back(processedSynonym);
        }
    }

    return processedSynonyms;
}

void QueryEvaluator::evaluateMultipleReturnValues(std::unordered_set<std::string>& finalSet, std::vector<std::string> requiredSynonyms) {
    std::vector<std::string> processedSynonyms = removeAllAttrRefs(requiredSynonyms);
    // check all the required synonyms are in the result table
    std::vector<std::unordered_map<std::string, std::string>> crossJoinMapList = getCrossJoinMapList(processedSynonyms);
	if (crossJoinMapList.empty()) {
		// Case 1: All required synonyms are in the result table
		addEntriesToFinalWithResultOnly(finalSet, requiredSynonyms);
	}
	for (auto map : crossJoinMapList) {
		if (result->getRows().empty()) {
			// Case 2: All required synonyms are not in the result table
			addEntriesToFinalWithOnlyCrossJoin(finalSet, requiredSynonyms, map);
		} else {
			// Case 3: Some required synonyms are in the result table and some are not
			addEntriesToFinalWithCrossJoinAndResult(finalSet, requiredSynonyms, map);
		}
	}
}

std::unordered_set<string> QueryEvaluator::evaluateQuery() {

    // Create a new result table for storing query results.
    result = std::make_shared<ResultTable>();
    result->setAsTruthTable();
    // create a vector of Clauses
    std::vector<std::shared_ptr<Clause>> clauses;

    // Check if the query is valid. If not, return an error message.
    if (!parsingResult.isQueryValid()) {
        unordered_set<string> error;
        error.insert(parsingResult.getErrorMessage());
        return error;
    }
    vector<SuchThatClause> suchThatClauses = parsingResult.getSuchThatClauses();
    // Add such-that-strategies based on the relationship specified in the query.
    for (auto clause : suchThatClauses) {
        clauses.push_back(std::make_shared<SuchThatClause>(clause));
    }
    
    vector<PatternClause> patternClauses = parsingResult.getPatternClauses();
    // Add PatternStrategy if pattern clause exists in the query.
    for (auto clause : patternClauses) {
        clauses.push_back(std::make_shared<PatternClause>(clause));
    }
    
    vector<WithClause> withClauses = parsingResult.getWithClauses();
    for (auto clause : withClauses) {
        clauses.push_back(std::make_shared<WithClause>(clause));
    }

    // Evaluate the query using the strategies and compile the results.
    bool isFirstStrategy = true;
    bool isOnlyBoolean = true;
    for (auto& clause : clauses) {
        shared_ptr<ResultTable> tempResult;
        unique_ptr<QueryEvaluationStrategy> strategy;

        // get the strategy based on the clause type
        // make unique pointer to the clause

        auto it = clauseToStrategiesMap.find(clause->getTypeName());
        if (it != clauseToStrategiesMap.end()) {
            strategy = it->second(clause);
        } else {
            throw "No such strategy found";
        }

        // evaluate the strategy
        if (clause->getTypeName() == "WithClause") {
            tempResult = strategy->evaluateQuery(*pkbReaderManager, parsingResult, *clause, result);
        } else {
            tempResult = strategy->evaluateQuery(*pkbReaderManager, parsingResult, *clause);
        }


        if (tempResult->isTableTrue()) {
            if (handleTableTrue(clause)) {
                continue;
            } else {
                break;
            }
        }

        // if it is a false table, we can break early since the result will be false
        if (tempResult->isTableFalse()) {
            if (handleTableFalse(clause)) {
                result = tempResult;
                break;
            } else {
                continue;
            }
        }

        if (isFirstStrategy) {
            isFirstStrategy = false;
            if (clause->getClauseOperation() == Clause::ClauseOperations::AND) {
                result = tempResult;
            } else {
                //
//                result = result->populateWithInverse(tempResult);
            }
        }
        else {
            // if it is a non true and non empty table, join the result with the tempResult
            if (clause->getClauseOperation() == Clause::ClauseOperations::AND) {
                result = result->joinOnColumns(tempResult);
            } else {
                // if it is a non true and non empty table, join the result with the tempResult
//                result = result->getInverse(tempResult);
            }
        }
    }

    // Retrieve and return the results based on the required synonym.
    std::vector<std::string> requiredSynonyms = parsingResult.getRequiredSynonyms();
    std::unordered_set<std::string> finalSet;

    const string requiredSynonym = requiredSynonyms[0];
    const string requiredSynonymForCheck = ParsingResult::isAttrRef(requiredSynonym) ? ParsingResult::getSynFromAttrRef(requiredSynonym) : requiredSynonym;
    std::string requiredType = parsingResult.getRequiredSynonymType(requiredSynonym);
    if (requiredSynonyms.size() == 1) {
        if (requiredSynonym == "BOOLEAN") {
            if (result->isTableTrue() || !result->isEmpty()) {
                return unordered_set<string>{"TRUE"};
            }
            else {
                return unordered_set<string>{"FALSE"};
            }
        }

        if (result->isTableFalse()) {
            return {};
        }

        unordered_set<string> currentResult;
        if (result->hasColumn(requiredSynonymForCheck)) {
            currentResult = result->getColumnValues(requiredSynonymForCheck);
        }
        else {
            //return all statement/variables/whatever
            if (result->isTableTrue() || !result->isEmpty() || isFirstStrategy) {
                currentResult = getAllEntities(requiredType);;
            }
        }

        if (ParsingResult::isAttrRef(requiredSynonym)) {
            convertToAttrSet(requiredSynonym, currentResult, finalSet);
        }
        else {
            finalSet = currentResult;
        }

        return finalSet;
    } else {
        if (result->isTableFalse()) return {};
		evaluateMultipleReturnValues(finalSet, requiredSynonyms);
    }
    return finalSet;
}

// Retrieves all entities of a specified type.
// Returns a vector of strings representing these entities.
std::unordered_set<std::string> QueryEvaluator::getAllEntities(const std::string& requiredType) {
    std::unordered_set<string> entities;
    // Find the entity retriever for the required type and get the entities.
    auto it = entityFactory.find(requiredType);
    if (it != entityFactory.end()) {
        auto variantEntities = it->second();
        if (std::holds_alternative<std::unordered_set<int>>(variantEntities)) {
            for (int entity : std::get<std::unordered_set<int>>(variantEntities)) {
                entities.insert(std::to_string(entity));
            }
        }
        else {
            for (const string& entity : std::get<std::unordered_set<string>>(variantEntities)) {
                entities.insert(entity);
            }
        }
    }
    else {
        throw "Unknown type of entity required";
    }

    return entities;
}

bool QueryEvaluator::handleTableTrue(shared_ptr<Clause> clause) {
    Clause::ClauseOperations op = clause->getClauseOperation();
        if (op == Clause::ClauseOperations::AND) {
            result->setAsTruthTable();
            return true;
        }
        else if (op == Clause::ClauseOperations::NOT) {
//            result->setAsFalseTable();
            return false;
        }

}

bool QueryEvaluator::handleTableFalse(shared_ptr<Clause> clause) {
    if (clause->getClauseOperation() == Clause::ClauseOperations::AND) {
        return true;
    }
    else if (clause->getClauseOperation() == Clause::ClauseOperations::NOT) {
        return false;
    }
}



// Initializes the strategy factory with various query evaluation strategies..
void QueryEvaluator::initializeStrategyFactory() {



    // Mapping of query types to their corresponding strategies.
    QueryEvaluator::suchThatStrategyFactory = {
            {TokenType::Follows, []() { return std::make_unique<FollowsStrategy>(); }},
            {TokenType::FollowsT, []() { return std::make_unique<FollowsStrategy>(); }},
            {TokenType::Parent, []() { return std::make_unique<ParentStrategy>(); }},
            {TokenType::ParentT, []() { return std::make_unique<ParentStrategy>(); }},
            {TokenType::UsesS, []() { return std::make_unique<UsesStrategy>(); }},
            {TokenType::ModifiesS, []() { return std::make_unique<ModifiesStrategy>(); }},
            {TokenType::ModifiesP, []() { return std::make_unique<ModifiesPStrategy>(); }},
            {TokenType::UsesP, []() { return std::make_unique<UsesPStrategy>(); }},
            {TokenType::Calls, []() { return std::make_unique<CallsStrategy>(); }},
            {TokenType::CallsT, []() { return std::make_unique<CallsStrategy>(); }},
            {TokenType::Next, []() { return std::make_unique<NextStrategy>(); }},
            {TokenType::NextT, []() { return std::make_unique<NextStrategy>(); }},
            {TokenType::Affects, []() { return std::make_unique<AffectsStrategy>(); }},
            // Additional strategies can be added here as needed.
    };

    QueryEvaluator::patternStrategyFactory = {
            {"assign", []() { return std::make_unique<AssignPatternStrategy>(); }},
            {"while", []() { return std::make_unique<WhilePatternStrategy>();}},
            {"if", []() { return std::make_unique<IfPatternStrategy>();}}
    };

    QueryEvaluator::clauseToStrategiesMap = {
            {"SuchThatClause", [this](shared_ptr<Clause> clause)-> std::unique_ptr<QueryEvaluationStrategy> {
                auto suchThatClause = dynamic_cast<SuchThatClause*>(clause.get());
                if (suchThatClause) {
                    TokenType suchThatRelationship = suchThatClause->getRelationship().getType();
                    auto it = suchThatStrategyFactory.find(suchThatRelationship);
                    if (it != suchThatStrategyFactory.end()) {
                        return it->second();
                    }
                }
            }},
            {"PatternClause", [this](shared_ptr<Clause> clause) -> std::unique_ptr<QueryEvaluationStrategy> {
                auto patternClause = dynamic_cast<PatternClause*>(clause.get());
                if (patternClause) {
                    string patternType = parsingResult.getPatternClauseType(*patternClause);
                    auto it = patternStrategyFactory.find(patternType);
                    if (it != patternStrategyFactory.end()) {
                        return it->second();
                    }

                }
            }},
            {"WithClause", [](shared_ptr<Clause> clause) -> std::unique_ptr<QueryEvaluationStrategy> { return std::make_unique<WithStrategy>(); }}
    };
}

// Initializes the entity factory for retrieving different types of entities.
void QueryEvaluator::initializeEntityFactory() {
    entityFactory = {
        // Mapping of entity types to functions that retrieve these entities.
        {"assign", [&]() {
            return variant<unordered_set<int>, unordered_set<string>>(pkbReaderManager->getAssignReader()->getAllEntities());
        }},
        {"call", [&]() {
            return variant<unordered_set<int>, unordered_set<string>>(pkbReaderManager->getCallReader()->getAllEntities());
        }},
        {"constant", [&]() {
            return variant<unordered_set<int>, unordered_set<string>>(pkbReaderManager->getConstantReader()->getAllEntities());
        }},
        {"if", [&]() {
            return variant<unordered_set<int>, unordered_set<string>>(pkbReaderManager->getIfReader()->getAllEntities());
        }},
        {"print", [&]() {
            return variant<unordered_set<int>, unordered_set<string>>(pkbReaderManager->getPrintReader()->getAllEntities());
        }},
        {"read", [&]() {
            return variant<unordered_set<int>, unordered_set<string>>(pkbReaderManager->getReadReader()->getAllEntities());
        }},
        {"stmt", [&]() {
            return variant<unordered_set<int>, unordered_set<string>>(pkbReaderManager->getStatementReader()->getAllEntities());
        }},
        {"while", [&]() {
            return variant<unordered_set<int>, unordered_set<string>>(pkbReaderManager->getWhileReader()->getAllEntities());
        }},

        // Entities returning unordered_set<string>
        {"variable", [&]() {
            return variant<unordered_set<int>, unordered_set<string>>(pkbReaderManager->getVariableReader()->getAllEntities());
        }},
        {"procedure", [&]() {
            return variant<unordered_set<int>, unordered_set<string>>(pkbReaderManager->getProcedureReader()->getAllEntities());
        }}
        // Additional entity types can be added here as needed.


    };
}

string QueryEvaluator::join(const unordered_set<string>& elements, const string& delimiter) {
    string result;
    for (const auto& element : elements) {
        if (!result.empty()) {
            result += delimiter;
        }
        result += element;
    }
    return result;
}



void QueryEvaluator::convertToAttrSet(const std::string &synonym, std::unordered_set<std::string> &valueSet,
                                      std::unordered_set<std::string> &attrSet) {
    if (ParsingResult::isAttrRef(synonym)) {
        for (const string& value : valueSet) {
            attrSet.insert(convertToAttr(synonym, value));
        }
    } else {
        attrSet = valueSet;
    };
}

string QueryEvaluator::convertToAttr(const string& synonym , string ref) {
    // check take the syn par from the AttrRef
    string declaredSynonymType = parsingResult.getRequiredSynonymType(synonym);
    // check the type of Attr
    string attrType = ParsingResult::getAttrFromAttrRef(synonym);
    if (attrType == "stmt#" || attrType == "value") {
        return ref;
    } else if (attrType == "procName") {
        return convertToProcName(declaredSynonymType, ref);
    } else if (attrType == "varName") {
        return convertToVarName(declaredSynonymType, ref);
    }
    return "";
}


string QueryEvaluator::convertToProcName(const std::string& declaredSynonym, std::string ref) {
    initializeProcNameMap();
    // find from the map the corresponding method based on the declaredSynonym and call the method to return the string
    if (declaredSynonym == "procedure") {
        return ref;
    }
    int refInt = stoi(ref);
    // add a check if exists first
    if (procNameMap.find(declaredSynonym) != procNameMap.end()) {
            return procNameMap.at(declaredSynonym)(refInt);
    } else {
        throwNoSuchMethodException();
    }

}


string QueryEvaluator::convertToVarName(const std::string& declaredSynonym, std::string ref) {
    initializeVarNameMap();
    // find from the map the corresponding method based on the declaredSynonym and call the method to return the string
    if (declaredSynonym == "variable") {
        return ref;
    }
    int refInt = stoi(ref);
    if (varNameMap.find(declaredSynonym) != varNameMap.end()) {
        return varNameMap.at(declaredSynonym)(refInt);
    } else {
        throwNoSuchMethodException();
    }
}

void QueryEvaluator::throwNoSuchMethodException() {
    throw "No such method for the declared synonym";
}


void QueryEvaluator::initializeProcNameMap() {
    this->procNameMap = {
            {"call",      [this](int ref) -> std::string {
                // Assuming getCallProcName is a valid method for demonstration
                shared_ptr<CallProcNameReader> callProcNameReader = pkbReaderManager->getCallProcNameReader();
                return callProcNameReader->getCalledProcedureName(ref);
            }}
    };
}

void QueryEvaluator::initializeVarNameMap() {
    this->varNameMap = {
            {"read",     [this](int ref) -> std::string {
                // Assuming getReadVarName is a valid method for demonstration
                shared_ptr<ReadVarNameReader> readVarNameReader = pkbReaderManager->getReadVarNameReader();
                return readVarNameReader->getReadVariableName(ref);
            }},
            {"print",    [this](int ref) -> std::string {
                // Assuming getPrintVarName is a valid method for demonstration
                shared_ptr<PrintVarNameReader> printVarNameReader = pkbReaderManager->getPrintVarNameReader();
                return printVarNameReader->getPrintVariableName(ref);
            }}
    };
}




// ai-gen end
