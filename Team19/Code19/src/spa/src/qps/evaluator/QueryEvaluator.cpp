#include "QueryEvaluator.h"
#include "qps/evaluator/strategies/PatternStrategy.h"
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
    vector<SuchThatClause> suchThatClauses = parsingResult.getSuchThatClauses();
    // Add such-that-strategies based on the relationship specified in the query.
    for (auto clause : suchThatClauses) {
        TokenType suchThatRelationship = clause.getRelationship().getType();
        auto it = strategyFactory.find(suchThatRelationship);
        if (it != strategyFactory.end()) {
            addStrategy(it->second());
        }
    }
    
    vector<PatternClause> patternClauses = parsingResult.getPatternClauses();
    // Add PatternStrategy if pattern clause exists in the query.
    for (auto clause : patternClauses) {
        addStrategy(std::make_unique<PatternStrategy>());
    }
    
    /*vector<WithClause> withClauses = parsingResult.getWithClauses();
    for (auto cluase : withClauses) {

    }*/

    // Evaluate the query using the strategies and compile the results.
    bool isFirstStrategy = true;
    int suchThatCounter = 0;
    int patternCounter = 0;
    for (auto& strategy : strategies) {
        if (suchThatCounter < suchThatClauses.size()) {
            result = strategy->evaluateQuery(*pkbReaderManager, parsingResult, suchThatClauses[suchThatCounter]);
            suchThatCounter++;
        }
        else if (patternCounter < patternClauses.size()) {
            result = strategy->evaluateQuery(*pkbReaderManager, parsingResult, patternClauses[patternCounter]);
            patternCounter++;
        }
        if (isFirstStrategy) {
            
            
            if (result->isEmpty() && !result->isTableTrue()) {
                return {};
            }

            // if it is not a truth table we still need to populate the result table
            if (!result->isTableTrue()) {
                isFirstStrategy = false;
            }
        }
        else {
            result = result->joinOnColumns(result);
        }
    }

    // Retrieve and return the results based on the required synonym.
    std::vector<std::string> requiredSynonyms = parsingResult.getRequiredSynonyms();
    std::unordered_set<std::string> finalSet;
    for (auto requiredSynonym : requiredSynonyms) {
        std::string requiredType = parsingResult.getRequiredSynonymType(requiredSynonym);

        if (result->hasColumn(requiredSynonym)) {
            unordered_set<string> currentResult = result->getColumnValues(requiredSynonym);
            finalSet.insert(currentResult.begin(), currentResult.end());
        }
        else {
            //return all statement/variables/whatever
            if (result->isTableTrue() || !result->isEmpty() || isFirstStrategy) {
                unordered_set<string> currentResult = getAllEntities(requiredType);;
                finalSet.insert(currentResult.begin(), currentResult.end());
            }
            
        }
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



// Initializes the strategy factory with various query evaluation strategies.
void QueryEvaluator::initializeStrategyFactory() {

    // Mapping of query types to their corresponding strategies.
    QueryEvaluator::strategyFactory = {
            {TokenType::Follows, []() { return std::make_unique<FollowsStrategy>(); }},
            {TokenType::FollowsT, []() { return std::make_unique<FollowsStrategy>(); }},
            {TokenType::Parent, []() { return std::make_unique<ParentStrategy>(); }},
            {TokenType::ParentT, []() { return std::make_unique<ParentStrategy>(); }},
            {TokenType::UsesS, []() { return std::make_unique<UsesStrategy>(); }},
            {TokenType::ModifiesS, []() { return std::make_unique<ModifiesStrategy>(); }},
            {TokenType::ModifiesP, []() { return std::make_unique<ModifiesPStrategy>(); }},
            {TokenType::UsesP, []() { return std::make_unique<UsesPStrategy>(); }},
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
        }},
        {"procedure", [&]() {
            return variant<unordered_set<int>, unordered_set<string>>(pkbReaderManager->getProcedureReader()->getAllEntities());
        }}
        // Additional entity types can be added here as needed.


    };
}

