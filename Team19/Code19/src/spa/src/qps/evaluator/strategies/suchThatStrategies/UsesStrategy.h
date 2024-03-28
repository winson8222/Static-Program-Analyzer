#pragma once

#include "qps/evaluator/strategies/suchThatStrategies/StmtEntStrategy.h"

using namespace std;

class UsesStrategy : public StmtEntStrategy {
private:
    std::shared_ptr<UsesSReader> usesSReader;



public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;
    void processBothSynonyms(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) override;
    void processFirstParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) override ;
    void processSecondParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) override;
    void processBothConstants(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable) override;


};
