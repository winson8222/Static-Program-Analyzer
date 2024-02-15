#include "FollowsStrategy.h"
#include "qps/parser/Token.h" // Include the Token header

using namespace std;

// The FollowsStrategy class evaluates queries to find follows relationships in a program.
// A follows relationship is defined between two statements (stmtRef, stmtRef), 
// where a stmtRef can be a wildcard, an integer, or a synonym.

unordered_set<string> FollowsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) {
    string requiredSynonym = parsingResult.getRequiredSynonym();
    string variant = parsingResult.getSuchThatClauseRelationship().getValue();
    unordered_set<string> result;

    // Obtain readers from PKBReaderManager
    this->followsReader = pkbReaderManager.getFollowsReader();
    this->followsTReader = pkbReaderManager.getFollowsTReader();
    this->statementReader = pkbReaderManager.getStatementReader();

    const Token& suchThatFirstParam = parsingResult.getSuchThatClauseFirstParam();
    const Token& suchThatSecondParam = parsingResult.getSuchThatClauseSecondParam();

    if (suchThatFirstParam.getValue() == requiredSynonym) {
        processFirstParam(suchThatSecondParam, variant, result);
    }
    else if (suchThatSecondParam.getValue() == requiredSynonym) {
        processSecondParam(suchThatFirstParam, variant, result);
    }
    else if (isBothParamsWildcard(suchThatFirstParam, suchThatSecondParam)) {
        const unordered_set<int>& follows = statementReader->getAllStatements();
        fillResult(follows, result);
    }
    else if (isBothParamsInteger(suchThatFirstParam, suchThatSecondParam)) {
        processIntegerParams(suchThatFirstParam, suchThatSecondParam, result);
    }

    return result;
}



// Additional helper methods for readability
void FollowsStrategy::processFirstParam(const Token& secondParam, const string& variant,
    unordered_set<string>& result) {
    // Implementation of processing when the first parameter matches the required synonym
    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(secondParam.getValue());
        const unordered_set<int>& follows = (variant == "Follows") ?
            followsReader->getPreFollows(stmtNum) :
            followsTReader->getPreFollowsT(stmtNum);
        fillResult(follows, result);
    }
    else if (secondParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& follows = (variant == "Follows") ?
            followsReader->getAllPreFollows() :
            followsTReader->getAllPreFollowsT();
        fillResult(follows, result);
    }
}

void FollowsStrategy::processSecondParam(const Token& firstParam, const string& variant,
    unordered_set<string>& result) {
    // Implementation of processing when the second parameter matches the required synonym
    if (firstParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(firstParam.getValue());
        const unordered_set<int>& follows = (variant == "Follows") ?
            followsReader->getPostFollows(stmtNum) :
            followsTReader->getPostFollowsT(stmtNum);
        fillResult(follows, result);
    }
    else if (firstParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& follows = (variant == "Follows") ?
            followsReader->getAllPostFollows() :
            followsTReader->getAllPostFollowsT();
        fillResult(follows, result);
    }
}



void FollowsStrategy::processIntegerParams(const Token& firstParam, const Token& secondParam,
    unordered_set<string>& result) {
    // Implementation for processing when both parameters are integers
    int firstStmtNum = stoi(firstParam.getValue());
    int secondStmtNum = stoi(secondParam.getValue());

    if (followsReader->hasFollows(firstStmtNum, secondStmtNum)) {
        const unordered_set<int>& follows = statementReader->getAllStatements();
        fillResult(follows, result);
    }
}
