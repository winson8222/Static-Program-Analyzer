#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include <memory>
#include <vector>
#include <string>
#include "../pkb/PKBReader.h"  // Your Program Knowledge Base interface header
#include "ParsingResult.h" // Your ParsingResult class header

class QueryResult; // Forward declaration for the query result class

class QueryEvaluator {
private:
    PKBReader pkb; // Shared pointer to the Program Knowledge Base
    ParsingResult& parsingResult; // Reference to the ParsingResult object

public:
    // Constructor
    explicit QueryEvaluator(PKBReader pkb, ParsingResult& parsingResult) : pkb(pkb), parsingResult(parsingResult) {};

    // Main method to evaluate queries based on ParsingResult
    QueryResult evaluateQuery();

private:


    // Methods for evaluating different aspects of the query based on ParsingResult
    QueryResult evaluateSuchThat();
    QueryResult evaluatePattern();
    QueryResult evaluateModifies();
    QueryResult evaluateUses();
    QueryResult evaluateParents();
    QueryResult evaluateFollows();

    // Combine results from various parts of the query
    QueryResult combineResults(const std::vector<QueryResult>& results);

    // Additional helper methods as needed
};

#endif // QUERYEVALUATOR_H
