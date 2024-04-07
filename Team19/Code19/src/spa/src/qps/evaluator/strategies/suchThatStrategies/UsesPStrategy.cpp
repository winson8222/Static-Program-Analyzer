#include "UsesPStrategy.h"
#include <string>
#include <memory>
#include <unordered_set>


std::shared_ptr<ResultTable> UsesPStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                  const ParsingResult &parsingResult,
                                                                  const Clause &clause,
                                                                  std::shared_ptr<ResultTable> result) {
    setIntermediateResultTable(result);
    return evaluateQuery(pkbReaderManager, parsingResult, clause);
}

std::shared_ptr<ResultTable> UsesPStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = std::make_shared<ResultTable>();
    std::shared_ptr<UsesPReader> usesPReader = pkbReaderManager.getUsesPReader();
    setReader(usesPReader);
    setBothParams(clause);

//    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);

    Token firstParam = getFirstParam();
    Token secondParam = getSecondParam();
    if (isBothParamsSynonym(firstParam, secondParam)) {
        this->processBothSynonyms(parsingResult, resultTable);
    } else if (isParamOfType(firstParam, TokenType::IDENT)) {
        this->processFirstParam(parsingResult, resultTable);
    } else if (isParamOfType(secondParam, TokenType::IDENT)) {
        this->processSecondParam(parsingResult, resultTable);
    } else {
        this->processBothConstants(parsingResult, resultTable);
    }

    return resultTable;
}


