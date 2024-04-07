#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "qps/evaluator/strategies/suchThatStrategies/StmtEntStrategy.h"

class UsesStrategy : public StmtEntStrategy {
private:


public:

	std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;
    std::shared_ptr<ResultTable> evaluateQueryOptimised(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, std::shared_ptr<ResultTable> result) override;
};
