#pragma once
#include "SuchThatStrategy.h"

class EntEntStrategy : public SuchThatStrategy {

public:
    ~EntEntStrategy() override = default;

    virtual void processBothSynonyms(const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable) = 0;
    virtual void processFirstParam(const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable) = 0;
    virtual void processSecondParam(const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable) = 0;
    virtual void processBothConstants(const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable) = 0;

};