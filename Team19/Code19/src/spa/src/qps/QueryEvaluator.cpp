#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "PKBReader.h" // Include your PKBReader header
#include "ParsingResult.h" // Include your ParsingResult header

using namespace std;

class QueryEvaluator {
private:
    shared_ptr<PKBReader> pkbReader;

public:
    QueryEvaluator(shared_ptr<PKBReader> pkb) : pkbReader(move(pkb)) {}

    void evaluateQuery(const ParsingResult& parsingResult) {
        if (parsingResult.getSuchThatClauseRelationship()) {
            // For simplicity, assuming the relationship is "Follows"
            auto firstParam = parsingResult.getSuchThatClauseFirstParam();
            auto secondParam = parsingResult.getSuchThatClauseSecondParam();

            // Convert parameters to integers for PKBReader API
            int stmt1 = stoi(firstParam.first); // Assuming stmt numbers are directly provided as strings
            int stmt2 = stoi(secondParam.first); // Adjust based on actual parameter format

            auto result = pkbReader->getPostFollows(stmt1);
            bool queryResult = result.find(stmt2) != result.end();

            cout << "Query Result: " << (queryResult ? "TRUE" : "FALSE") << endl;
        }
        // Extend this with more conditions to handle other clause types
    }
};

#endif // QUERYEVALUATOR_H