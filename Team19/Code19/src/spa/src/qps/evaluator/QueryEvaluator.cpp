#include <variant>
#include "qps/evaluator/QueryEvaluator.h"
#include "qps/evaluator/ResultTable.h"
#include "qps/evaluator/strategies/WithStrategy.h"

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
        std::string synonymSyn = ParsingResult::getSynFromAttrRef(synonym);
        std::string ref = map.at(synonymSyn);
        std::string convertedAttr = convertToAttr(synonym, ref);
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
            std::string requiredSynonymForChecking;
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
		unordered_set<std::string> currentResult = getAllEntities(requiredType);
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

    for (const std::string& synonym : requiredSynonyms) {
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

std::shared_ptr<ResultTable> QueryEvaluator::getInverse(std::shared_ptr<ResultTable> table) {
    if (table->isTableTrue()) {
        return std::make_shared<ResultTable>();
    }
    std::shared_ptr<ResultTable> inverseTable = std::make_shared<ResultTable>();
    // add columns to the inverse table
    vector<string> colSet = table->getColSet();
    inverseTable->insertAllColumns(colSet);

    populateEntityCombinations(inverseTable);
    return inverseTable->excludeOnColumns(table);
}

void QueryEvaluator::populateEntityCombinations(std::shared_ptr<ResultTable> table) {
    vector<string> allCol = table->getColSet();

    if (allCol.size() == 1) {
        string col = allCol[0];
        string type = parsingResult.getRequiredSynonymType(col);
        auto entities = getAllEntities(type);
        table->populateWithOneColumn(col, entities);
        return;
    }
    string colA = allCol[0];
    string colB = allCol[1];

    // Retrieve the entity types for the specified columns from ParsingResult
    std::string typeA = parsingResult.getRequiredSynonymType(colA);
    std::string typeB = parsingResult.getRequiredSynonymType(colB);

    // Fetch entities for both types
    auto entitiesA = getAllEntities(typeA);
    auto entitiesB = getAllEntities(typeB);

    // Generate all possible combinations of entities A and B
    table->populateWithTwoColumns(colA, colB, entitiesA, entitiesB);

}


std::unordered_set<std::string> QueryEvaluator::evaluateQuery() {

    // Create a new result table for storing query results.
    result = std::make_shared<ResultTable>();
    result->setAsTruthTable();
    // create a vector of Clauses


    // Check if the query is valid. If not, return an error message.
    if (!parsingResult.isQueryValid()) {
        std::unordered_set<std::string> error;
        error.insert(parsingResult.getErrorMessage());
        return error;
    }

    const std::vector<std::shared_ptr<Clause>> clauses = addAllClauses(parsingResult);


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

        tempResult = strategy->evaluateQuery(*pkbReaderManager, parsingResult, *clause);



        if (tempResult->isTableTrue()) {
            if (handleTableTrue(clause)) {
                continue;
            } else {
                tempResult->setTableFalse();
                result = tempResult;
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
                std::shared_ptr<ResultTable> inversedResult;
                inversedResult = getInverse(tempResult);
                result = inversedResult;
            }
        }
        else {
            // if it is a non true and non empty table, join the result with the tempResult
            if (clause->getClauseOperation() == Clause::ClauseOperations::AND) {
                result = result->joinOnColumns(tempResult);
            } else {
                // if it is a non true and non empty table, join the result with the tempResult
                std::shared_ptr<ResultTable> inversedResult;
                inversedResult = getInverse(tempResult);
                result = result->joinOnColumns(inversedResult);
            }
        }
    }

    // Retrieve and return the results based on the required synonym.
    std::vector<std::string> requiredSynonyms = parsingResult.getRequiredSynonyms();
    std::unordered_set<std::string> finalSet;

    const std::string requiredSynonym = requiredSynonyms[0];
    const std::string requiredSynonymForCheck = ParsingResult::isAttrRef(requiredSynonym) ? ParsingResult::getSynFromAttrRef(requiredSynonym) : requiredSynonym;
    std::string requiredType = parsingResult.getRequiredSynonymType(requiredSynonym);
    if (requiredSynonyms.size() == 1) {
        if (parsingResult.isBooleanSelection()) {
            if (result->isTableTrue() || !result->isEmpty()) {
                return std::unordered_set<std::string>{"TRUE"};
            }
            else {
                return std::unordered_set<std::string>{"FALSE"};
            }
        }

        if (result->isTableFalse()) {
            return {};
        }

        std::unordered_set<std::string> currentResult;
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
// Returns a std::vector of std::strings representing these entities.
std::unordered_set<std::string> QueryEvaluator::getAllEntities(const std::string& requiredType) {
    std::unordered_set<std::string> entities;
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
            for (const std::string& entity : std::get<std::unordered_set<std::string>>(variantEntities)) {
                entities.insert(entity);
            }
        }
    }
    else {
        throw "Unknown type of entity required";
    }

    return entities;
}

bool QueryEvaluator::handleTableTrue(std::shared_ptr<Clause> clause) {
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
            return std::variant<std::unordered_set<int>, std::unordered_set<std::string>>(pkbReaderManager->getAssignReader()->getAllEntities());
        }},
        {"call", [&]() {
            return std::variant<std::unordered_set<int>, std::unordered_set<std::string>>(pkbReaderManager->getCallReader()->getAllEntities());
        }},
        {"constant", [&]() {
            return std::variant<std::unordered_set<int>, std::unordered_set<std::string>>(pkbReaderManager->getConstantReader()->getAllEntities());
        }},
        {"if", [&]() {
            return std::variant<std::unordered_set<int>, std::unordered_set<std::string>>(pkbReaderManager->getIfReader()->getAllEntities());
        }},
        {"print", [&]() {
            return std::variant<std::unordered_set<int>, std::unordered_set<std::string>>(pkbReaderManager->getPrintReader()->getAllEntities());
        }},
        {"read", [&]() {
            return std::variant<std::unordered_set<int>, std::unordered_set<std::string>>(pkbReaderManager->getReadReader()->getAllEntities());
        }},
        {"stmt", [&]() {
            return std::variant<std::unordered_set<int>, std::unordered_set<std::string>>(pkbReaderManager->getStatementReader()->getAllEntities());
        }},
        {"while", [&]() {
            return std::variant<std::unordered_set<int>, std::unordered_set<std::string>>(pkbReaderManager->getWhileReader()->getAllEntities());
        }},

        // Entities returning std::unordered_set<std::string>
        {"variable", [&]() {
            return std::variant<std::unordered_set<int>, std::unordered_set<std::string>>(pkbReaderManager->getVariableReader()->getAllEntities());
        }},
        {"procedure", [&]() {
            return std::variant<std::unordered_set<int>, std::unordered_set<std::string>>(pkbReaderManager->getProcedureReader()->getAllEntities());
        }}
        // Additional entity types can be added here as needed.


    };
}

std::string QueryEvaluator::join(const std::unordered_set<std::string>& elements, const std::string& delimiter) {
    std::string result;
    for (const auto& element : elements) {
        if (!result.empty()) {
            result += delimiter;
        }
        result += element;
    }
    return result;
}

void QueryEvaluator::convertToAttrSet(const std::string &synonym, std::unordered_set<std::string> &valueSet, std::unordered_set<std::string> &attrSet) {
    if (ParsingResult::isAttrRef(synonym)) {
        for (const std::string& value : valueSet) {
            attrSet.insert(convertToAttr(synonym, value));
        }
    } else {
        attrSet = valueSet;
    };
}

std::string QueryEvaluator::convertToAttr(const std::string& synonym , std::string ref) {
    // check take the syn par from the AttrRef
    std::string declaredSynonymType = parsingResult.getRequiredSynonymType(synonym);
    // check the type of Attr
    std::string attrType = ParsingResult::getAttrFromAttrRef(synonym);
    if (attrType == "stmt#" || attrType == "value") {
        return ref;
    } else if (attrType == "procName") {
        return convertToProcName(declaredSynonymType, ref);
    } else if (attrType == "varName") {
        return convertToVarName(declaredSynonymType, ref);
    }
    return "";
}


std::string QueryEvaluator::convertToProcName(const std::string& declaredSynonym, std::string ref) {
    initializeProcNameMap();
    // find from the map the corresponding method based on the declaredSynonym and call the method to return the std::string
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


std::string QueryEvaluator::convertToVarName(const std::string& declaredSynonym, std::string ref) {
    initializeVarNameMap();
    // find from the map the corresponding method based on the declaredSynonym and call the method to return the std::string
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
                std::shared_ptr<CallProcNameReader> callProcNameReader = pkbReaderManager->getCallProcNameReader();
                return callProcNameReader->getCalledProcedureName(ref);
            }}
    };
}

void QueryEvaluator::initializeVarNameMap() {
    this->varNameMap = {
            {"read",     [this](int ref) -> std::string {
                // Assuming getReadVarName is a valid method for demonstration
                std::shared_ptr<ReadVarNameReader> readVarNameReader = pkbReaderManager->getReadVarNameReader();
                return readVarNameReader->getReadVariableName(ref);
            }},
            {"print",    [this](int ref) -> std::string {
                // Assuming getPrintVarName is a valid method for demonstration
                std::shared_ptr<PrintVarNameReader> printVarNameReader = pkbReaderManager->getPrintVarNameReader();
                return printVarNameReader->getPrintVariableName(ref);
            }}
    };
}

std::vector<std::shared_ptr<Clause>> QueryEvaluator::addAllClauses(ParsingResult &parsingResult) {
    std::vector<std::shared_ptr<Clause>> clauses;
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
    return clauses;
}



// ai-gen end
