#include "ModifiesStrategy.h"

std::shared_ptr<ResultTable> ModifiesStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult)
{
    auto resultTable = make_shared<ResultTable>();
    this->ModifiesSReader = pkbReaderManager.getModifiesSReader();
    this->statementReader = pkbReaderManager.getStatementReader();

    const Token& suchThatFirstParam = parsingResult.getSuchThatClauseFirstParam();
    const Token& suchThatSecondParam = parsingResult.getSuchThatClauseSecondParam();

    if (suchThatFirstParam.getType() == TokenType::IDENT && suchThatSecondParam.getType() == TokenType::IDENT) {
        processBothSynonyms(suchThatFirstParam, suchThatSecondParam, resultTable);
    } else if (suchThatFirstParam.getType() == TokenType::IDENT) {
        processFirstSynonymSecondInteger(suchThatFirstParam, suchThatSecondParam, resultTable);
    } else if (suchThatSecondParam.getType() == TokenType::IDENT) {
        processFirstIntegerSecondSynonym(suchThatFirstParam, suchThatSecondParam, resultTable);
    } else {
        throw "Invalid Query!";
    }



}
