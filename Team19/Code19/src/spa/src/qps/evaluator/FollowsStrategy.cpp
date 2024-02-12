#include "FollowsStrategy.h"
#include "../Parser/Token.h" // Make sure to include the Token header

using namespace std;

unordered_set<string> FollowsStrategy::evaluateQuery(PKBReader& pkbReader, const ParsingResult& parsingResult) {
    string requiredSynonym = parsingResult.getRequiredSynonym();
    unordered_set<string> result;
    const Token& suchThatRelationship = parsingResult.getSuchThatClauseRelationship();
    const Token& suchThatFirstParam = parsingResult.getSuchThatClauseFirstParam();
    const Token& suchThatSecondParam = parsingResult.getSuchThatClauseSecondParam();

    if (suchThatFirstParam.getValue() == requiredSynonym) {
        if (suchThatSecondParam.getType() == TokenType::INTEGER) {
            const unordered_set<int>& follows = pkbReader.getPreFollows(stoi(suchThatSecondParam.getValue()));
            for (int i : follows) {
                result.insert(to_string(i));
            }
        }
        else if (suchThatSecondParam.getType() == TokenType::Wildcard) {
            const unordered_set<int>& follows = pkbReader.getAllPreFollows();
            for (int i : follows) {
                result.insert(to_string(i));
            }
        }
        else {
            // Return an empty set for other cases
            return unordered_set<string>();
        }
    }
    else if (suchThatSecondParam.getValue() == requiredSynonym) {
        if (suchThatFirstParam.getType() == TokenType::INTEGER) {
            const unordered_set<int>& follows = pkbReader.getPostFollows(stoi(suchThatFirstParam.getValue()));
            for (int i : follows) {
                result.insert(to_string(i));
            }
        }
        else if (suchThatSecondParam.getType() == TokenType::Wildcard) {
            const unordered_set<int>& follows = pkbReader.getAllPostFollows();
            for (int i : follows) {
                result.insert(to_string(i));
            }
        }
        else {
            // Return an empty set for other cases
            return unordered_set<string>();
        }
    }

    return result;
}

