#ifndef QUERYEVALUATOR_H
#define QUERYEVALUATOR_H

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include "../pkb/PKBManager.h" // Include your PKBReader header
#include "ParsingResult.h" // Include your ParsingResult header
#include "Token.h" // Include your Token header

using namespace std;

class QueryEvaluator {
private:
    shared_ptr<PKBReader> pkbReader;
    ParsingResult& parsingResult;
    string requiredSynonym;
    unordered_set<string> result;

public:
    QueryEvaluator(shared_ptr<PKBReader> pkb, ParsingResult& parsingResult)
            : pkbReader(pkb), parsingResult(parsingResult) {}


    void evaluateQuery() {
            // Get the declared synonyms
            requiredSynonym = parsingResult.getRequiredSynonym();
            string requiredType = parsingResult.getRequiredSynonymType();

            const unordered_map<string, string>& declared = parsingResult.getDeclaredSynonyms();
            // check what is the type of synonym required
            if (requiredType == "stmt") {
                unordered_set<int> allStmts = pkbReader->getAllStmts();
                for (int i : allStmts) {
                    result.insert(to_string(i));
                }
                string suchThatType = parsingResult.getSuchThatClauseRelationship().getValue();
                if (suchThatType == "Follows") {
                    unordered_set<string> newResults = evaluateFollows();
                    combineResults(newResults);
                }

//                } else if (suchThatType == "Modifies") {
//                    evaluateModifies();
//                } else if (suchThatType == "Uses") {
//                    evaluateUses();
//                } else if (suchThatType == "Parent") {
//                    evaluateParents();
//                }


            } else if (requiredType == "variable") {
                // Get all the read statements
                const unordered_set<std::string>& allVariables = pkbReader->getAllVariables();
                // Print the results

            } else if (requiredType == "assign") {
                // Get all the print statements
                const unordered_set<int> &allAssigns = pkbReader->getAllAssigns();
                // Print the results
            }




        // Extend this with more conditions to handle other clause types
    }

    unordered_set<string> evaluateFollows() {
        const unordered_set<int>& stmts = pkbReader->getAllStmts();
        const Token& suchThatRelationship = parsingResult.getSuchThatClauseRelationship();
        const Token& suchThatFirstParam = parsingResult.getSuchThatClauseFirstParam();
        const Token& suchThatSecondParam = parsingResult.getSuchThatClauseSecondParam();

        if (suchThatFirstParam.getValue() == requiredSynonym) {
            // Get the follows relationship
            if (suchThatSecondParam.getType() == TokenType::INTEGER) {
                // Get the all follows relationship with the secondparam as the integer specified
                const unordered_set<int> &follows = pkbReader->getPreFollows(
                        stoi(suchThatSecondParam.getValue()));
                for (int i : follows) {
                    result.insert(to_string(i));
                }
            } else if (suchThatSecondParam.getType() == TokenType::Wildcard) {
                // Get the all follows relationship with the secondparam as the wildcard
                const unordered_set<int> &follows = pkbReader->getPostFollows(-1);
                // insert the results
                for (int i : follows) {
                    result.insert(to_string(i));
                }
            } else {
                // return an empty set
                unordered_set<string> empty;
                return empty;
            }
        } else if (suchThatSecondParam.getValue() == requiredSynonym) {
            // Get the follows relationship
            if (suchThatFirstParam.getType() == TokenType::INTEGER) {
                // Get the all follows relationship with the first as the integer specified
                const unordered_set<int> &follows = pkbReader->getPostFollows(
                        stoi(suchThatFirstParam.getValue()));
                for (int i : follows) {
                    result.insert(to_string(i));
                }
            } else if (suchThatSecondParam.getType() == TokenType::Wildcard) {
                // Get the all follows relationship with the first param as the wildcard
                const unordered_set<int> &follows = pkbReader->getPostFollows(-1);
                // insert the results
                for (int i : follows) {
                    result.insert(to_string(i));
                }
            } else {
                unordered_set<string> empty;
                return empty;
            }
        }
    }

    void combineResults(const std::unordered_set<std::string>& newResult) {
        std::unordered_set<std::string> intersection;

        for (const auto& item : newResult) {
            if (result.find(item) != result.end()) {
                intersection.insert(item);
            }
        }

        result = intersection;
    }



};

#endif // QUERYEVALUATOR_H
