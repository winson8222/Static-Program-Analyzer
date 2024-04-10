#include "ModifiesStrategy.h"


std::shared_ptr<ResultTable> ModifiesStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                    const ParsingResult &parsingResult,
                                                                    const Clause &clause,
                                                                    std::shared_ptr<ResultTable> result) {
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, std::string>> reader = pkbReaderManager.getModifiesSReader();

    setReader(reader);

    return getOptimallyEvaluatedResultTable(parsingResult, pkbReaderManager, clause, result);
}

std::shared_ptr<ResultTable> ModifiesStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = std::make_shared<ResultTable>();
    setBothParams(clause);

    std::shared_ptr<ModifiesSReader> modifiesSReader = pkbReaderManager.getModifiesSReader();
    setReader(modifiesSReader);


    setBothParams(clause);

    return getEvaluatedResultTable(pkbReaderManager, parsingResult, resultTable);
}

