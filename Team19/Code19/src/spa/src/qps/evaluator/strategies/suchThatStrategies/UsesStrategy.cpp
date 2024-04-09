#include "UsesStrategy.h"
#include <memory>
#include <unordered_map>


std::shared_ptr<ResultTable> UsesStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                  const ParsingResult &parsingResult,
                                                                  const Clause &clause,
                                                                  std::shared_ptr<ResultTable> result) {
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, std::string>> reader = pkbReaderManager.getUsesSReader();

    setReader(reader);

    return getOptimallyEvaluatedResultTable(parsingResult, pkbReaderManager, clause, result);
}


std::shared_ptr<ResultTable> UsesStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = std::make_shared<ResultTable>();
    setBothParams(clause);

    std::shared_ptr<UsesSReader> usesReader = pkbReaderManager.getUsesSReader();
    setReader(usesReader);

    setBothParams(clause);
    return getEvaluatedResultTable(pkbReaderManager, parsingResult, resultTable);
}

