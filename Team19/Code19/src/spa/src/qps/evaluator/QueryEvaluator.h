#pragma
#include <vector> // For storing multiple strategies
#include "QueryEvaluationStrategy.h" // Include the strategy interface
#include <memory>
#include "qps/evaluator/ResultTable.h"

class QueryEvaluator {
private:
    std::shared_ptr<PKBReaderManager> pkbReaderManager;
    ParsingResult& parsingResult;
    std::shared_ptr<ResultTable> result;
    std::vector<std::unique_ptr<QueryEvaluationStrategy>> strategies; // Store multiple strategies

public:
    QueryEvaluator(std::shared_ptr<PKBReaderManager> pkbReaderManager, ParsingResult& parsingResult);
    std::vector<string> evaluateQuery();
    void addStrategy(std::unique_ptr<QueryEvaluationStrategy> strategy); // Method to add strategies
};
