#pragma once

#include "qps/evaluator/strategies/patternStrategies/PatternStrategy.h"


class ControlPatternStrategy : public PatternStrategy {
protected:
    std::shared_ptr<ResultTable> getEvaluatedResultTable(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable) override;
};



