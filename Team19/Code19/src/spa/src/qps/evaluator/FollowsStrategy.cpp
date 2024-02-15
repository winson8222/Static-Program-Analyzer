#include "FollowsStrategy.h"
#include "../Parser/Token.h" // Include the Token header

using namespace std;

// The FollowsStrategy class evaluates queries to find follows relationships in a program.
// A follows relationship is defined between two statements (stmtRef, stmtRef), 
// where a stmtRef can be a wildcard, an integer, or a synonym.

unordered_set<string> FollowsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) {
    string requiredSynonym = parsingResult.getRequiredSynonym();
    string variant = parsingResult.getSuchThatClauseRelationship().getValue();
    unordered_set<string> result;

    // Obtain readers from PKBReaderManager
    auto followsReader = pkbReaderManager.getFollowsReader();
    auto followsTReader = pkbReaderManager.getFollowsTReader();
    auto statementReader = pkbReaderManager.getStatementReader();

    const Token& suchThatFirstParam = parsingResult.getSuchThatClauseFirstParam();
    const Token& suchThatSecondParam = parsingResult.getSuchThatClauseSecondParam();

    if (suchThatFirstParam.getValue() == requiredSynonym) {
        processFirstParam(suchThatSecondParam, variant, followsReader, followsTReader, result);
    }
    else if (suchThatSecondParam.getValue() == requiredSynonym) {
        processSecondParam(suchThatFirstParam, variant, followsReader, followsTReader, result);
    }
    else if (isBothParamsWildcard(suchThatFirstParam, suchThatSecondParam)) {
        const unordered_set<int>& follows = statementReader->getAllStatements();
        fillResult(follows, result);
    }
    else if (isBothParamsInteger(suchThatFirstParam, suchThatSecondParam)) {
        processIntegerParams(suchThatFirstParam, suchThatSecondParam, followsReader, statementReader, result);
    }

    return result;
}

void FollowsStrategy::fillResult(const unordered_set<int>& follows, unordered_set<string>& result) {
    for (int statement : follows) {
        result.insert(to_string(statement));
    }
}

// Additional helper methods for readability
void FollowsStrategy::processFirstParam(const Token& secondParam, const string& variant,
    shared_ptr<FollowsReader> followsReader,
    shared_ptr<FollowsTReader> followsTReader,
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
    shared_ptr<FollowsReader> followsReader,
    shared_ptr<FollowsTReader> followsTReader,
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

bool FollowsStrategy::isBothParamsWildcard(const Token& firstParam, const Token& secondParam) {
    // Implementation to check if both parameters are wildcards
    return firstParam.getType() == TokenType::Wildcard && secondParam.getType() == TokenType::Wildcard;
}

bool FollowsStrategy::isBothParamsInteger(const Token& firstParam, const Token& secondParam) {
    // Implementation to check if both parameters are integers
    return firstParam.getType() == TokenType::INTEGER && secondParam.getType() == TokenType::INTEGER;
}

void FollowsStrategy::processIntegerParams(const Token& firstParam, const Token& secondParam,
    shared_ptr<FollowsReader> followsReader,
    shared_ptr<StatementReader> statementReader,
    unordered_set<string>& result) {
    // Implementation for processing when both parameters are integers
    int firstStmtNum = stoi(firstParam.getValue());
    int secondStmtNum = stoi(secondParam.getValue());

    if (followsReader->hasFollows(firstStmtNum, secondStmtNum)) {
        const unordered_set<int>& follows = statementReader->getAllStatements();
        fillResult(follows, result);
    }
}
