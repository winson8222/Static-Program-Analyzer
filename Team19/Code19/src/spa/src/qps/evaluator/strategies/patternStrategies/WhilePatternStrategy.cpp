#include "WhilePatternStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>


std::shared_ptr<ResultTable> WhilePatternStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                     const ParsingResult &parsingResult,
                                                                     const Clause &clause,
                                                                     std::shared_ptr<ResultTable> result) {
    setIntermediateResultTable(result);
    return evaluateQuery(pkbReaderManager, parsingResult, clause);
}

std::shared_ptr<ResultTable> WhilePatternStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();
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
    std::string firstColName = this->relationShip.getValue();
    std::string secondColName = this->firstParam.getValue();
    insertColsToTable(this->relationShip, this->firstParam, resultTable);
    insertRowsWithTwoCols(firstParam, relationShip,  parsingResult, whilePatternReader, resultTable);
}

void WhilePatternStrategy::processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
    std::string firstColName = this->relationShip.getValue();
    insertSingleColToTable(this->relationShip, result);
    std::unordered_set<int> allStmts;
    std::string firstParamValue;
    std::string secondParamValue;
    firstParamValue = extractQuotedExpression(firstParam);

//    secondParamValue = ShuntingYard::convertToPostfix(secondParamValue);
    allStmts = whilePatternReader->getStatementNumbersOfWhileControlVariable(firstParamValue);
    insertStmtRowsWithSingleCol(allStmts, result, firstColName);
}


void WhilePatternStrategy::processWildcard(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
    std::string firstColName = this->relationShip.getValue();
    insertSingleColToTable(this->relationShip, result);
    std::unordered_set<int> allStmts;
    allStmts = whilePatternReader->getAllStatementNumbersOfWhileControlVariables();
    insertStmtRowsWithSingleCol(allStmts, result, firstColName);
}
