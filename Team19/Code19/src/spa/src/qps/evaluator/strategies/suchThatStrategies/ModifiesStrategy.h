#pragma once

#include "StmtEntStrategy.h"


using namespace std;

class ModifiesStrategy : public StmtEntStrategy {
private:
    std::shared_ptr<ModifiesSReader> modifiesSReader;



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

