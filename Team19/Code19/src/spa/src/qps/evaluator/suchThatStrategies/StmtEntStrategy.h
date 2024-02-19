#pragma once


#include "qps/evaluator/suchThatStrategies/SuchThatStrategy.h"
#ifndef SPA_STMTENTSTRATEGY_H
#define SPA_STMTENTSTRATEGY_H


class StmtEntStrategy : public SuchThatStrategy{
public:
    ~StmtEntStrategy() override = default;

    // for clauses when there are two parameters, one INTEGER and one IDENT
    virtual void processIntegerAndIdentParams(const Token& firstParam, const Token& secondParam,
                                      unordered_set<string>& result) = 0;

    virtual void processFirstParam(const Token& secondParam, const string& variant,
                                   unordered_set<string>& result) = 0;

    virtual void processSecondParam(const Token& firstParam, const string& variant,
                                    unordered_set<string>& result) = 0;

    virtual void processBothParam(const Token& firstParam, const Token& secondParam,
                                  unordered_set<string>& result) = 0;

protected:
    static bool isBothParamsWildcard(const Token& firstParam, const Token& secondParam);
    static bool isParamsIntegerAndIdent(const Token& firstParam, const Token& secondParam);
    static void fillResult(const unordered_set<int>& follows, unordered_set<string>& result);

};


#endif //SPA_STMTENTSTRATEGY_H
