#include "QueryEvaluator.h"
#include "PatternStrategy.h"
#include "qps/evaluator/ResultTable.h"
#include <variant>

using namespace std;

QueryEvaluator::QueryEvaluator(std::shared_ptr<PKBReaderManager> pkbReaderManager, ParsingResult& parsingResult)
    : pkbReaderManager(pkbReaderManager), parsingResult(parsingResult) {
    initializeStrategyFactory();
    initializeEntityFactory();
}

void QueryEvaluator::addStrategy(std::unique_ptr<QueryEvaluationStrategy> strategy) {
    strategies.push_back(std::move(strategy));
}

std::vector<string> QueryEvaluator::evaluateQuery() {

    // create result table
    result = std::make_shared<ResultTable>();

    // if query is not valid, return error message and stop evaluation
    if (!parsingResult.isQueryValid()) {
        // convert error message to vector<string>
        vector<string> error;
        error.push_back(parsingResult.getErrorMessage());
        return error;
    }
    
    // Handle SuchThatClause relationships
    std::string suchThatRelationship = parsingResult.getSuchThatClauseRelationship().getValue();
    auto it = strategyFactory.find(suchThatRelationship);
    if (it != strategyFactory.end()) {
        addStrategy(it->second());
    }

    // Handle PatternClause
    if (!parsingResult.getPatternClauseRelationship().getValue().empty()) {
        addStrategy(std::make_unique<PatternStrategy>());
    }

    bool isFirstStrategy = true;
    for (auto& strategy : strategies) {
        if (isFirstStrategy) {
            result = strategy->evaluateQuery(*pkbReaderManager, parsingResult);
            isFirstStrategy = false;
        }
        else {
            result = result->joinOnColumns(strategy->evaluateQuery(*pkbReaderManager, parsingResult));
        }
    }

    std::string requiredSynonym = parsingResult.getRequiredSynonym();
    std::string requiredType = parsingResult.getRequiredSynonymType();

    if (result->hasColumn(requiredSynonym)) {
        return result->getColumnValues(requiredSynonym);
    }
    else {
        //return all statement/variables/whatever
        return getAllEntities(requiredType);
	}
 

}

std::vector<std::string> QueryEvaluator::getAllEntities(const std::string& requiredType) {
    std::vector<std::string> entities;

    auto it = entityFactory.find(requiredType);
    if (it != entityFactory.end()) {
        auto variantEntities = it->second();
        if (std::holds_alternative<std::unordered_set<int>>(variantEntities)) {
            for (int entity : std::get<std::unordered_set<int>>(variantEntities)) {
                entities.push_back(std::to_string(entity));
            }
        }
        else {
            for (string entity : std::get<std::unordered_set<string>>(variantEntities)) {
                entities.push_back(entity);
            }
        }
    }
    else {
        throw "Unknown type of entity required";
    }

    return entities;
}



// Initialize the strategy factory map
void QueryEvaluator::initializeStrategyFactory() {
    QueryEvaluator::strategyFactory = {
        {"Follows", []() { return std::make_unique<FollowsStrategy>(); }},
        {"Follows*", []() { return std::make_unique<FollowsStrategy>(); }},
        {"Parent", []() { return std::make_unique<ParentStrategy>(); }},
        {"Parent*", []() { return std::make_unique<ParentStrategy>(); }},
        {"Uses", []() { return std::make_unique<UsesStrategy>(); }},
        {"Modifies", []() { return std::make_unique<ModifiesStrategy>(); }}
        // Add additional strategies here as needed
    };
}

void QueryEvaluator::initializeEntityFactory() {
    entityFactory = {
        // Entities returning std::vector<int>
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
        }}
        // Add additional entity types here as needed
    };
}

