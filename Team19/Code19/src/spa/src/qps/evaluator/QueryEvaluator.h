#pragma
#include <vector> // For storing multiple strategies
#include "QueryEvaluationStrategy.h" // Include the strategy interface
#include <memory>


class QueryEvaluator {
private:
    std::shared_ptr<PKBReader> pkbReader;
    ParsingResult& parsingResult;
    std::unordered_set<std::string> result;
    std::vector<std::unique_ptr<QueryEvaluationStrategy>> strategies; // Store multiple strategies

public:
    QueryEvaluator(std::shared_ptr<PKBReader> pkb, ParsingResult& parsingResult);
    void evaluateQuery();
    void addStrategy(std::unique_ptr<QueryEvaluationStrategy> strategy); // Method to add strategies
    void combineResults(const std::unordered_set<std::string>& newResult); // Combine results from multiple strategies
};
