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
			if (crossJoinMap.find(requiredSynonym) != crossJoinMap.end()) {
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

void QueryEvaluator::evaluateMultipleReturnValues(std::unordered_set<std::string>& finalSet, std::vector<std::string> requiredSynonyms) {
	std::vector<std::unordered_map<std::string, std::string>> crossJoinMapList = getCrossJoinMapList(requiredSynonyms);
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

    // Check if the query is valid. If not, return an error message.
    if (!parsingResult.isQueryValid()) {
        unordered_set<string> error;
        error.insert(parsingResult.getErrorMessage());
        return error;
    }
    vector<SuchThatClause> suchThatClauses = parsingResult.getSuchThatClauses();
    // Add such-that-strategies based on the relationship specified in the query.
    for (auto clause : suchThatClauses) {
        TokenType suchThatRelationship = clause.getRelationship().getType();
        auto it = suchThatStrategyFactory.find(suchThatRelationship);
        if (it != suchThatStrategyFactory.end()) {
            addStrategy(it->second());
        }
    }
    
    vector<PatternClause> patternClauses = parsingResult.getPatternClauses();
    // Add PatternStrategy if pattern clause exists in the query.
    for (auto clause : patternClauses) {
        string patternType = parsingResult.getPatternClauseType(clause);
        auto it = patternStrategyFactory.find(patternType);
        if (it != patternStrategyFactory.end()) {
            addStrategy(it->second());
        }
    }
    
    vector<WithClause> withClauses = parsingResult.getWithClauses();
    for (auto cluase : withClauses) {
        addStrategy(std::make_unique<WithStrategy>());
    }

    // Evaluate the query using the strategies and compile the results.
    bool isFirstStrategy = true;
    int suchThatCounter = 0;
    int patternCounter = 0;
    int withCounter = 0;
    for (auto& strategy : strategies) {
        shared_ptr<ResultTable> tempResult;
        if (suchThatCounter < suchThatClauses.size()) {
            tempResult = strategy->evaluateQuery(*pkbReaderManager, parsingResult, suchThatClauses[suchThatCounter]);
            suchThatCounter++;
        }
        else if (patternCounter < patternClauses.size()) {
            tempResult = strategy->evaluateQuery(*pkbReaderManager, parsingResult, patternClauses[patternCounter]);
            patternCounter++;
        }
        else if (withCounter < withClauses.size()) {
            tempResult = strategy->evaluateQuery(*pkbReaderManager, parsingResult, withClauses[withCounter], result);
			withCounter++;
		}
      
        // if it is a true table skip to next strategy
        if (tempResult->isTableTrue()) {
            result = tempResult;
            continue;
        }

        // if it is a false table, we can break early since the result will be false
        if (tempResult->isTableFalse()) {
            result = tempResult;
            break;
        }

        if (isFirstStrategy) {
            // if it is a false table, we can break early since the result will be false
            isFirstStrategy = false;
            result = tempResult;
        }
        else {
            // if it is a non true and non empty table, join the result with the tempResult
            result = result->joinOnColumns(tempResult);
        }
    }

    // Retrieve and return the results based on the required synonym.
    std::vector<std::string> requiredSynonyms = parsingResult.getRequiredSynonyms();
    std::unordered_set<std::string> finalSet;

    if (requiredSynonyms.size() == 1) {
        if (requiredSynonyms[0] == "BOOLEAN") {
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
        std::string requiredType = parsingResult.getRequiredSynonymType(requiredSynonyms[0]);

        if (result->hasColumn(requiredSynonyms[0])) {
            unordered_set<string> currentResult = result->getColumnValues(requiredSynonyms[0]);
            finalSet.insert(currentResult.begin(), currentResult.end());
        }
        else {
            //return all statement/variables/whatever
            if (result->isTableTrue() || !result->isEmpty() || isFirstStrategy) {
                unordered_set<string> currentResult = getAllEntities(requiredType);;
                finalSet.insert(currentResult.begin(), currentResult.end());
            }

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
            for (string entity : std::get<std::unordered_set<string>>(variantEntities)) {
                entities.insert(entity);
            }
        }
    }
    else {
        throw "Unknown type of entity required";
    }

    return entities;
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

bool QueryEvaluator::isSynAttrRef(const string& ref) {
    return ref.find(".") != string::npos;
}

string QueryEvaluator::convertToAttr(string synonym , string ref) {
    string declaredSynonym = ParsingResult::getSynFromAttrRef(synonym);
    string attrType = ParsingResult::getAttrFromAttrRef(synonym);
    if (attrType == "stmt#" || attrType == "value") {
            return ref;
    } else if (attrType == "procName") {
        return convertToProcName(declaredSynonym, ref);
    } else if (attrType == "varName") {
        return convertToVarName(declaredSynonym, ref);
    }
    return "";
}


string QueryEvaluator::convertToProcName(const std::string& declaredSynonym, std::string ref) {
    if (declaredSynonym == "procedure") {
        return ref;
    }

    if (declaredSynonym == "call") {
        return pkbReaderManager->getCallProcNameReader()->getCalledProcedureName(stoi(ref));
    } else {
        return "";
    }
}


string QueryEvaluator::convertToVarName(std::string declaredSynonym, std::string ref) {
    if (declaredSynonym == "variable") {
        return ref;
    }

    if (declaredSynonym == "read") {
        return pkbReaderManager->getReadVarNameReader()->getReadVariableName(stoi(ref));
    }

    if (declaredSynonym == "print") {
        return pkbReaderManager->getPrintVarNameReader()->getPrintVariableName(stoi(ref));
    }
    return "";
}
// ai-gen end
