#include "AffectsStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>


std::shared_ptr<ResultTable> AffectsStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                    const ParsingResult &parsingResult,
                                                                    const Clause &clause,
                                                                    std::shared_ptr<ResultTable> result) {
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, int>> reader = pkbReaderManager.getAffectsReader();

    setReader(reader);

    return getOptimallyEvaluatedResultTable(parsingResult, pkbReaderManager, clause, result);
}

std::shared_ptr<ResultTable> AffectsStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, int>> affectsReader = pkbReaderManager.getAffectsReader();
    setReader(affectsReader);
    return getEvaluatedResultTable(pkbReaderManager, parsingResult, resultTable);
}
