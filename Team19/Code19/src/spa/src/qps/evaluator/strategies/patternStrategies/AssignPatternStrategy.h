#pragma once

#include <memory>
#include "qps/evaluator/strategies/patternStrategies/PatternStrategy.h"
#include "commons/ShuntingYard.h"

class AssignPatternStrategy : public PatternStrategy {
private:
    std::shared_ptr<AssignPatternReader> assignPatternReader;
    std::shared_ptr<AssignReader> assignReader;


public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;
    std::shared_ptr<ResultTable> evaluateQueryOptimised(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, std::shared_ptr<ResultTable> result) override;
    void processSynonyms(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) override;
    void processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) override;
    void processWildcard(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) override;
};
