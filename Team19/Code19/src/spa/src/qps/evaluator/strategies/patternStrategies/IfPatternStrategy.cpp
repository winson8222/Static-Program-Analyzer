#include "IfPatternStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>


std::shared_ptr<ResultTable> IfPatternStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                     const ParsingResult &parsingResult,
                                                                     const Clause &clause,
                                                                     std::shared_ptr<ResultTable> result) {
    setIntermediateResultTable(result);
    return evaluateQuery(pkbReaderManager, parsingResult, clause);
}

std::shared_ptr<ResultTable> IfPatternStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();
    this->ifPatternReader = pkbReaderManager.getIfPatternReader();
    this->ifReader = pkbReaderManager.getIfReader();


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

void IfPatternStrategy::processSynonyms(ParsingResult parsingResult, std::shared_ptr<ResultTable> resultTable) {
    std::string firstColName = this->relationShip.getValue();
    std::string secondColName = this->firstParam.getValue();
    insertColsToTable(this->relationShip, this->firstParam, resultTable);
    insertRowsWithTwoCols(this->firstParam, this->relationShip, parsingResult ,ifPatternReader, resultTable);
}

void IfPatternStrategy::processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
    std::string firstColName = this->relationShip.getValue();
    insertSingleColToTable(this->relationShip, result);
    std::unordered_set<int> allStmts;
    std::string firstParamValue;
    std::string secondParamValue;
    firstParamValue = extractQuotedExpression(firstParam);

//    secondParamValue = ShuntingYard::convertToPostfix(secondParamValue);
    allStmts = ifPatternReader->getStatementNumbersWithControlPattern(firstParamValue);
    insertStmtRowsWithSingleCol(allStmts, result, firstColName);
}

void IfPatternStrategy::processWildcard(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
    std::string firstColName = this->relationShip.getValue();
    insertSingleColToTable(this->relationShip, result);
    std::unordered_set<int> allStmts;
    allStmts = ifPatternReader->getAllStatementNumbersOfIfControlVariables();
    insertStmtRowsWithSingleCol(allStmts, result, firstColName);
}
