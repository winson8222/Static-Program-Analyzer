#pragma once

#include <memory>
#include "qps/evaluator/strategies/suchThatStrategies/StmtStmtStrategy.h"
#include "pkb/readers/relationships/AffectsReader.h"

class AffectsStrategy : public StmtStmtStrategy {
private:


public:
    // Override the evaluateQuery method to implement the Affects evaluation logic
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;
    std::shared_ptr<ResultTable> evaluateQueryOptimised(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, std::shared_ptr<ResultTable> result) override;
};
