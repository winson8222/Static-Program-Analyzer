#pragma once

#include "qps/evaluator/strategies/suchThatStrategies/EntEntStrategy.h"


using namespace std;

class ModifiesPStrategy : public EntEntStrategy {
private:
    std::shared_ptr<ModifiesPReader> modifiesPReader;



public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;
    void processBothSynonyms(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) override;
    void processFirstParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) override ;
    void processSecondParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) override;
    void processBothConstants(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) override;


};


