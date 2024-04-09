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
    whilePatternReader = pkbReaderManager.getWhilePatternReader();
    whileReader = pkbReaderManager.getWhileReader();


    const PatternClause *patternClause = dynamic_cast<const PatternClause *>(&clause);
    setBothParams(clause);
    Token relationship = patternClause->getRelationship();
    setRelationship(relationship);


    if (firstParam.getType() == TokenType::IDENT) {
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
    std::string firstColName = relationship.getValue();
    std::string secondColName = firstParam.getValue();
    insertColsToTable(relationship, firstParam, resultTable);
    insertRowsWithTwoCols(firstParam, relationship,  parsingResult, whilePatternReader, resultTable);
}

void WhilePatternStrategy::processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
    std::string firstColName = relationship.getValue();
    insertSingleColToTable(relationship, result);
    std::unordered_set<int> allStmts;
    std::string firstParamValue;
    std::string secondParamValue;
    firstParamValue = extractQuotedExpression(firstParam);

//    secondParamValue = ShuntingYard::convertToPostfix(secondParamValue);
    allStmts = whilePatternReader->getStatementNumbersOfWhileControlVariable(firstParamValue);
    insertStmtRowsWithSingleCol(allStmts, result, firstColName);
}


void WhilePatternStrategy::processWildcard(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) {
    std::string firstColName = relationship.getValue();
    insertSingleColToTable(relationship, result);
    std::unordered_set<int> allStmts;
    allStmts = whilePatternReader->getAllStatementNumbersOfWhileControlVariables();
    insertStmtRowsWithSingleCol(allStmts, result, firstColName);
}

