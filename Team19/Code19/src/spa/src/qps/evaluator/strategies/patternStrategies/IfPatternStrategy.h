#pragma once

#include "qps/evaluator/strategies/patternStrategies/ControlPatternStrategy.h"
#include "commons/ShuntingYard.h"

class IfPatternStrategy : public ControlPatternStrategy {
private:
    std::shared_ptr<IfPatternReader> ifPatternReader;
    std::shared_ptr<IfReader> ifReader;



public:

    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;
    std::shared_ptr<ResultTable> evaluateQueryOptimised(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, std::shared_ptr<ResultTable> result) override;
    void processSynonyms(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) override;
    void processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) override;
    void processWildcard(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) override;

};
