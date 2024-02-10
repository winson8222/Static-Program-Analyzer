#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "../pkb/PKBReader.h" // Include your PKBReader header
#include "ParsingResult.h" // Include your ParsingResult header
#include "Token.h" // Include your Token header

using namespace std;

class QueryEvaluator {
private:
    shared_ptr<PKBReader> pkbReader;

public:
    QueryEvaluator(shared_ptr<PKBReader> pkb) : pkbReader(move(pkb)) {}

    void evaluateQuery(const ParsingResult& parsingResult) {
            // Get the declared synonyms
            const string& required = parsingResult.getRequiredSynonym();
            const unordered_map<string, string>& declared = parsingResult.getDeclaredSynonyms();
            // check what is the type of synonym required
            if (required == "stmt") {
                // Get all the statements
                const unordered_set<int>& stmts = pkbReader->getAllStmts();
                // Print the results

            } else if (required == "variable") {
                // Get all the read statements
                const unordered_set<std::string>& allVariables = pkbReader->getAllVariables();
                // Print the results

            } else if (required == "assign") {
                // Get all the print statements
                const unordered_set<int> &allAssigns = pkbReader->getAllAssigns();
                // Print the results
            }

            // Get the such that clause
            const Token& suchThatRelationship = parsingResult.getSuchThatClauseRelationship();
            const Token& suchThatFirstParam = parsingResult.getSuchThatClauseFirstParam();
            const Token& suchThatSecondParam = parsingResult.getSuchThatClauseSecondParam();
            // check what is the type of relationship
            if (suchThatRelationship.getType() == TokenType::Follows) {

                if (suchThatFirstParam.getValue() == required) {
                    // Get the follows relationship
                    if (suchThatSecondParam.getType() == TokenType::INTEGER) {
                        // Get the all follows relationship with the secondparam as the integer specified
                        const unordered_set<int> &follows = pkbReader->getPreFollows(
                                stoi(suchThatSecondParam.getValue()));
                        // Print the results
                        // add other conditions such as wildcard
                    }
                }



        }
        // Extend this with more conditions to handle other clause types
    }
};

#endif // QUERYEVALUATOR_H
