#include "ParentStrategy.h"
#include "qps/parser/Token.h" // Include the Token header

using namespace std;

// The ParentStrategy class evaluates queries to find parents relationships in a program.
// A parents relationship is defined between two statements (stmtRef, stmtRef),
// where a stmtRef can be a wildcard, an integer, or a synonym.

std::shared_ptr<ResultTable> ParentStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) {
    string requiredSynonym = parsingResult.getRequiredSynonym();
    string variant = parsingResult.getSuchThatClauseRelationship().getValue();
    unordered_set<string> result;

    // Obtain readers from PKBReaderManager
    this->parentReader = pkbReaderManager.getParentReader();
    this->parentTTReader = pkbReaderManager.getParentTReader();
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
        const unordered_set<int>& parents = statementReader->getAllStatements();
        fillResult(parents, result);
    }
    else if (isBothParamsInteger(suchThatFirstParam, suchThatSecondParam)) {
        processIntegerParams(suchThatFirstParam, suchThatSecondParam, result);
    }

    return result;
}



// Additional helper methods for readability
void ParentStrategy::processFirstParam(const Token& secondParam, const string& variant,
                                        unordered_set<string>& result) {
    // Implementation of processing when the first parameter matches the required synonym
    if (secondParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(secondParam.getValue());
        const unordered_set<int>& parents = (variant == "Parent") ?
                                            parentReader->getParent(stmtNum) :
                                            parentTTReader->getParentT(stmtNum);
        fillResult(parents, result);
    }
    else if (secondParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& parents = (variant == "ParentT") ?
                                            parentReader->getAllParents() :
                                            parentTTReader->getAllParentTs();
        fillResult(parents, result);
    }
}

void ParentStrategy::processSecondParam(const Token& firstParam, const string& variant,
                                         unordered_set<string>& result) {
    // Implementation of processing when the second parameter matches the required synonym
    if (firstParam.getType() == TokenType::INTEGER) {
        int stmtNum = stoi(firstParam.getValue());
        const unordered_set<int>& parents = (variant == "Parent") ?
                                            parentReader->getChild(stmtNum) :
                                            parentTTReader->getChildT(stmtNum);
        fillResult(parents, result);
    }
    else if (firstParam.getType() == TokenType::Wildcard) {
        const unordered_set<int>& parents = (variant == "ParentT") ?
                                            parentReader->getAllChildren() :
                                            parentTTReader->getAllChildrenT();
        fillResult(parents, result);
    }
}



void ParentStrategy::processIntegerParams(const Token& firstParam, const Token& secondParam,
                                           unordered_set<string>& result) {
    // Implementation for processing when both parameters are integers
    int firstStmtNum = stoi(firstParam.getValue());
    int secondStmtNum = stoi(secondParam.getValue());

    if (parentReader->hasParent(firstStmtNum, secondStmtNum)) {
        const unordered_set<int>& parents = statementReader->getAllStatements();
        fillResult(parents, result);
    }
}
