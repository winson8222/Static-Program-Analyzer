#pragma once

#include "qps/evaluator/strategies/PatternStrategy.h"
#include "commons/ShuntingYard.h"

class WhilePatternStrategy : public PatternStrategy {
private:
    std::shared_ptr<WhilePatternReader> whilePatternReader;
    std::shared_ptr<WhileReader> whileReader;
    Token firstParam;
    Token secondParam;
    Token relationShip;


public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;
    void processSynonyms(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) override;
    void processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) override;
    void processWildcard(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) override;
};
