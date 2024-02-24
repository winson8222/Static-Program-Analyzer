#pragma
#include <vector> // For storing multiple strategies
#include <memory>
#include <map>
#include "QueryEvaluationStrategy.h" // Include the strategy interface
#include "qps/evaluator/ResultTable.h"
#include "qps/parser/Token.h"
#include "qps/evaluator/suchThatStrategies/FollowsStrategy.h" // Include FollowsStrategy
#include "qps/evaluator/suchThatStrategies/ParentStrategy.h" // Include ParentStrategy
#include "qps/evaluator/suchThatStrategies/ModifiesStrategy.h" // Include ModifiesStrategy
#include "qps/evaluator/suchThatStrategies/UsesStrategy.h" // Include UsesStrategy


class QueryEvaluator {
private:
    std::shared_ptr<PKBReaderManager> pkbReaderManager;
    ParsingResult& parsingResult;
    std::shared_ptr<ResultTable> result;
    std::vector<std::unique_ptr<QueryEvaluationStrategy>> strategies; // Store multiple strategies
    std::map<std::string, std::function<std::unique_ptr<QueryEvaluationStrategy>()>> strategyFactory;

public:
    QueryEvaluator(std::shared_ptr<PKBReaderManager> pkbReaderManager, ParsingResult& parsingResult);
    std::vector<string> evaluateQuery();
    std::vector<std::string> getAllEntities(const std::string& requiredType);
    
    void addStrategy(std::unique_ptr<QueryEvaluationStrategy> strategy); // Method to add strategies

    void QueryEvaluator::initializeStrategyFactory();
};
