#include "qps/evaluator/strategies/suchThatStrategies/NextStrategy.h"
#include <memory>
#include <string>
#include <unordered_set>
#include <utility>

std::shared_ptr<ResultTable> NextStrategy::evaluateQueryOptimised(PKBReaderManager &pkbReaderManager,
                                                                    const ParsingResult &parsingResult,
                                                                    const Clause &clause,
                                                                    std::shared_ptr<ResultTable> result) {
    // Determine if we're dealing with Next or Next*
    const auto* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->variant = suchClause->getRelationship().getValue();
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, int>> reader;
    if (variant == "Next") {
        reader = pkbReaderManager.getNextReader();
    } else if (variant == "Next*") {
        reader = pkbReaderManager.getNextTReader();
    }
    setReader(reader);

    return getOptimallyEvaluatedResultTable(parsingResult, pkbReaderManager, clause, result);
}

std::shared_ptr<ResultTable> NextStrategy::evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) {
    auto resultTable = std::make_shared<ResultTable>();
    const auto* suchClause = dynamic_cast<const SuchThatClause*>(&clause);
    this->variant = suchClause->getRelationship().getValue();
    setBothParams(clause);
    std::shared_ptr<IRelationshipReader<int, int>> reader;
    if (variant == "Next") {
        reader = pkbReaderManager.getNextReader();
    } else if (variant == "Next*") {
        reader = pkbReaderManager.getNextTReader();
    }
    setReader(reader);

    return getEvaluatedResultTable(pkbReaderManager, parsingResult, resultTable);
}


