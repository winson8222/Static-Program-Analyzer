#include "UsesPStrategy.h"
#include <string>
#include <memory>
#include <unordered_set>


std::shared_ptr<ResultTable> UsesPStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                  const ParsingResult &parsingResult,
                                                                  const Clause &clause,
                                                                  std::shared_ptr<ResultTable> result) {
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<std::string, std::string>> reader = pkbReaderManager.getUsesPReader();
    setReader(reader);
    return getOptimallyEvaluatedResultTable(parsingResult, pkbReaderManager, clause, result);
}

std::shared_ptr<ResultTable> UsesPStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause)
{
    auto resultTable = std::make_shared<ResultTable>();
    std::shared_ptr<UsesPReader> usesPReader = pkbReaderManager.getUsesPReader();
    setReader(usesPReader);
    setBothParams(clause);

//    const SuchThatClause* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    return getEvaluatedResultTable(pkbReaderManager, parsingResult, resultTable);
}


