#include "UsesStrategy.h"
#include <memory>
#include <unordered_map>


std::shared_ptr<ResultTable> UsesStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                  const ParsingResult &parsingResult,
                                                                  const Clause &clause,
                                                                  std::shared_ptr<ResultTable> result) {
    setIntermediateResultTable(result);
    return evaluateQuery(pkbReaderManager, parsingResult, clause);
}


std::shared_ptr<ResultTable> UsesStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = std::make_shared<ResultTable>();
    setBothParams(clause);

    std::shared_ptr<UsesSReader> usesReader = pkbReaderManager.getUsesSReader();
    setReader(usesReader);

    setBothParams(clause);

    if (isBothParamsSynonym(firstParam, secondParam)) {
        processBothSynonyms(parsingResult, resultTable, pkbReaderManager);
    } else if (firstParam.getType() == TokenType::IDENT) {
        processFirstParam(parsingResult, resultTable, pkbReaderManager);
    } else if (secondParam.getType() == TokenType::IDENT) {
        processSecondParam(parsingResult, resultTable, pkbReaderManager);
    } else {
        processBothConstants( parsingResult, resultTable);
    }
    return resultTable;
}

