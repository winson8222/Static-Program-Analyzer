#pragma once
#include "SuchThatStrategy.h"

class EntEntStrategy : public SuchThatStrategy {

public:
    ~EntEntStrategy() override = default;

    virtual void processBothSynonyms(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) = 0;
    virtual void processFirstParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) = 0;
    virtual void processSecondParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) = 0;
    virtual void processBothConstants(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable) = 0;
    virtual void processWildCards(const Token& firstParam, const Token& secondParam,std::shared_ptr<ResultTable> resultTable) = 0;

};