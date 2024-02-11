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
    unordered_set<string> result;

public:
    QueryEvaluator(shared_ptr<PKBReader> pkb, ParsingResult& parsingResult)
            : pkbReader(pkb), parsingResult(parsingResult) {}


    void evaluateQuery() {
            // Get the declared synonyms
            string requiredSynonym = parsingResult.getRequiredSynonym();
            string requiredType = parsingResult.getRequiredSynonymType();

            const unordered_map<string, string>& declared = parsingResult.getDeclaredSynonyms();
            // check what is the type of synonym required
            if (requiredType == "stmt") {
                string suchThatType = parsingResult.getSuchThatClauseRelationship().getValue();
                if (suchThatType == "") {
                    const unordered_set<int>& follows = pkbReader->getAllStmts();
                    for (int i : follows) {
                        result.insert(to_string(i));
                    }
				}
                if (suchThatType == "Follows") {
                    result = evaluateFollows();
                }
                // else if (suchThatType == "Parent") {
                   // evaluateParents();
                //}
//                } else if (suchThatType == "Modifies") {
//                    evaluateModifies();
//                } else if (suchThatType == "Uses") {
//                    evaluateUses();
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

    /**
     * Modifies the 'result' set to contain only elements that are also present in 'newResult'.
     * This function effectively computes the intersection of 'result' and 'newResult'.
     *
     * @param newResult The set with which the intersection is to be found.
     */
    void combineResults(const std::unordered_set<std::string>& newResult) {
        for (auto it = result.begin(); it != result.end(); ) {
            if (newResult.find(*it) == newResult.end()) {
                it = result.erase(it);
            }
            else {
                ++it;
            }
        }
    }




};
