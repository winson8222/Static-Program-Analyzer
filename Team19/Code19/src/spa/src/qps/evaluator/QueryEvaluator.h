#pragma
#include <vector> // For storing multiple strategies
#include <memory>
#include <map>
#include "QueryEvaluationStrategy.h" // Include the strategy interface
#include "qps/evaluator/ResultTable.h"
#include "qps/parser/Token.h"
#include "qps/evaluator/strategies/suchThatStrategies/FollowsStrategy.h" // Include FollowsStrategy
#include "qps/evaluator/strategies/suchThatStrategies/ParentStrategy.h" // Include ParentStrategy
#include "qps/evaluator/strategies/suchThatStrategies/ModifiesStrategy.h" // Include ModifiesStrategy
#include "qps/evaluator/strategies/suchThatStrategies/UsesStrategy.h" // Include UsesStrategy
#include <variant>


class QueryEvaluator {
private:
    std::shared_ptr<PKBReaderManager> pkbReaderManager;
    ParsingResult& parsingResult;
    std::shared_ptr<ResultTable> result;
    std::vector<std::unique_ptr<QueryEvaluationStrategy>> strategies; // Store multiple strategies
    std::map<TokenType, std::function<std::unique_ptr<QueryEvaluationStrategy>()>> strategyFactory; // Map of strategy factory
    std::map<std::string, std::function<std::variant<std::unordered_set<int>, std::unordered_set<std::string>>()>> entityFactory;
    std::vector<std::pair<std::unique_ptr<QueryEvaluationStrategy>, const Clause*>> strategyAndClausePairs;


public:
    QueryEvaluator(std::shared_ptr<PKBReaderManager> pkbReaderManager, ParsingResult& parsingResult);
    std::unordered_set<string> evaluateQuery();
    std::unordered_set<std::string> getAllEntities(const std::string& requiredType);
    
    void addStrategy(std::unique_ptr<QueryEvaluationStrategy> strategy); // Method to add strategies

    void initializeStrategyFactory(); // Method to initialize the strategy factory
    void initializeEntityFactory(); // Method to initialize the entity factory
};
