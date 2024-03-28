#pragma once

#include "qps/evaluator/strategies/suchThatStrategies/EntEntStrategy.h"

using namespace std;

class UsesPStrategy : public EntEntStrategy {
private:
    std::shared_ptr<UsesPReader> usesPReader;
    Token firstParam;
    Token secondParam;

public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;
    void processBothSynonyms(const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable) override;
    void processFirstParam(const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable) override ;
    void processSecondParam(const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable) override;
    void processBothConstants(const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable) override;


};
