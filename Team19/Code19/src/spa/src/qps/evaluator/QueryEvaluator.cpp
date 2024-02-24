#include "QueryEvaluator.h"
#include "PatternStrategy.h"
#include "qps/evaluator/ResultTable.h"
#include <variant>

using namespace std;

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

// Evaluates a query based on the strategies added.
// It returns a vector of strings representing the query results.
std::unordered_set<string> QueryEvaluator::evaluateQuery() {

    // Create a new result table for storing query results.
    result = std::make_shared<ResultTable>();

    // Check if the query is valid. If not, return an error message.
    if (!parsingResult.isQueryValid()) {
        unordered_set<string> error;
        error.insert(parsingResult.getErrorMessage());
        return error;
    }
    
    // Add such-that-strategies based on the relationship specified in the query.
    std::string suchThatRelationship = parsingResult.getSuchThatClauseRelationship().getValue();
    auto it = strategyFactory.find(suchThatRelationship);
    if (it != strategyFactory.end()) {
        addStrategy(it->second());
    }

    // Add PatternStrategy if pattern clause exists in the query.
    if (!parsingResult.getPatternClauseRelationship().getValue().empty()) {
        addStrategy(std::make_unique<PatternStrategy>());
    }

    // Evaluate the query using the strategies and compile the results.
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

    // Retrieve and return the results based on the required synonym.
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



// Initializes the strategy factory with various query evaluation strategies.
void QueryEvaluator::initializeStrategyFactory() {

    // Mapping of query types to their corresponding strategies.
    QueryEvaluator::strategyFactory = {
        {"Follows", []() { return std::make_unique<FollowsStrategy>(); }},
        {"Follows*", []() { return std::make_unique<FollowsStrategy>(); }},
        {"Parent", []() { return std::make_unique<ParentStrategy>(); }},
        {"Parent*", []() { return std::make_unique<ParentStrategy>(); }},
        {"Uses", []() { return std::make_unique<UsesStrategy>(); }},
        {"Modifies", []() { return std::make_unique<ModifiesStrategy>(); }}
        // Additional strategies can be added here as needed.
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
        }}
        // Additional entity types can be added here as needed.

    };
}

