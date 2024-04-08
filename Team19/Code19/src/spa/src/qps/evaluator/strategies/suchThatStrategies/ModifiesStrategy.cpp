#include "ModifiesStrategy.h"


std::shared_ptr<ResultTable> ModifiesStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                    const ParsingResult &parsingResult,
                                                                    const Clause &clause,
                                                                    std::shared_ptr<ResultTable> result) {
    setIntermediateResultTable(result);
    return evaluateQuery(pkbReaderManager, parsingResult, clause);
}

std::shared_ptr<ResultTable> ModifiesStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = std::make_shared<ResultTable>();
    setBothParams(clause);

    std::shared_ptr<ModifiesSReader> modifiesSReader = pkbReaderManager.getModifiesSReader();
    setReader(modifiesSReader);

    const Token& firstParam = getFirstParam();
    const Token& secondParam = getSecondParam();
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

