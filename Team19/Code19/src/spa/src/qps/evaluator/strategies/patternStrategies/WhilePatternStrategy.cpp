#include "WhilePatternStrategy.h"


std::shared_ptr<ResultTable> WhilePatternStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = make_shared<ResultTable>();
    this->whilePatternReader = pkbReaderManager.getWhilePatternReader();
    this->whileReader = pkbReaderManager.getWhileReader();


    const PatternClause *patternClause = dynamic_cast<const PatternClause *>(&clause);
    this->firstParam = patternClause->getFirstParam();
    this->secondParam = patternClause->getSecondParam();
    this->relationShip = patternClause->getRelationship();


    if (this->firstParam.getType() == TokenType::IDENT) {
        processSynonyms(parsingResult, resultTable);
    } else if (firstParam.getType() == TokenType::QuoutIDENT) {
        processQuotedIdent(parsingResult, resultTable);
    } else if (firstParam.getType() == TokenType::Wildcard) {
        processWildcard(parsingResult, resultTable);
    } else {
        throw "Invalid firstParam type";
    }

    return resultTable;

}

void WhilePatternStrategy::processSynonyms(ParsingResult parsingResult, std::shared_ptr<ResultTable> resultTable) {
    string firstColName = this->relationShip.getValue();
    string secondColName = this->firstParam.getValue();
    insertColsToTable(this->relationShip, this->firstParam, resultTable);
    std::unordered_set<int> allStmts;

    allStmts = whilePatternReader->getAllStatementNumbersOfWhileControlVariables();
    for (auto stmt : allStmts) {
        std::unordered_set<std::string> foundVariables = whilePatternReader->getControlVariablesOfWhileStatement(stmt);
        for (auto var : foundVariables) {
            pair<string, string> col1 = make_pair(firstParam.getValue(), var);
            pair<string, string> col2 = make_pair(relationShip.getValue(), to_string(stmt));
            insertRowToTable(col1, col2, resultTable);
        }
    }
}

void WhilePatternStrategy::processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
    string firstColName = this->relationShip.getValue();
    insertSingleColToTable(this->relationShip, result);
    std::unordered_set<int> allStmts;
    std::string firstParamValue;
    std::string secondParamValue;
    firstParamValue = extractQuotedExpression(firstParam);

//    secondParamValue = ShuntingYard::convertToPostfix(secondParamValue);
    allStmts = whilePatternReader->getStatementNumbersOfWhileControlVariable(firstParamValue);
    std::unordered_set<string> allStmtInString;
    convertIntSetToStringSet(allStmts, allStmtInString);
    insertRowsWithSingleColumn(firstColName, allStmtInString, result);
}


void WhilePatternStrategy::processWildcard(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
    string firstColName = this->relationShip.getValue();
    insertSingleColToTable(this->relationShip, result);
    std::unordered_set<int> allStmts;
    allStmts = whilePatternReader->getAllStatementNumbers();
    std::unordered_set<string> allStmtInString;
    convertIntSetToStringSet(allStmts, allStmtInString);
    insertRowsWithSingleColumn(firstColName, allStmtInString, result);
}