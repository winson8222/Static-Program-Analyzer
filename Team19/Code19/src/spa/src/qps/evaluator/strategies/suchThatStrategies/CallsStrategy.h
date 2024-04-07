#pragma once

#include "qps/evaluator/strategies/suchThatStrategies/EntEntStrategy.h"

class CallsStrategy : public EntEntStrategy {
private:
    std::string variant;


public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;
    std::shared_ptr<ResultTable> evaluateQueryOptimised(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, std::shared_ptr<ResultTable> result) override;

};
