//
// Created by Winson Zheng on 22/2/24.
//

#ifndef SPA_STMTENTSTRATEGY_H
#define SPA_STMTENTSTRATEGY_H


#include "SuchThatStrategy.h"
using namespace std;

class StmtEntStrategy : public SuchThatStrategy {

public:
    ~StmtEntStrategy() override = default;

    virtual void processBothSynonyms(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable);
    virtual void processFirstParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable);
    virtual void processSecondParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable);
    virtual void processBothConstants(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
            ,std::shared_ptr<ResultTable> resultTable);
    virtual void processBothWildCards(std::shared_ptr<ResultTable> resultTable);
};


#endif //SPA_STMTENTSTRATEGY_H
