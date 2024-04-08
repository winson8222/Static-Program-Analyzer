#pragma once

#include <memory>
#include "qps/evaluator/strategies/suchThatStrategies/EntEntStrategy.h"

class UsesPStrategy : public EntEntStrategy {
private:


public:
	std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;
    std::shared_ptr<ResultTable> evaluateQueryOptimised(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, std::shared_ptr<ResultTable> result) override;

};
