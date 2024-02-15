#pragma once


#include "qps/evaluator/suchThatStrategies/SuchThatStrategy.h"

using namespace std;
/**
 * @brief Strategy class for evaluating "such that" clauses involving relationships between statements.
 *
 * This class extends the SuchThatStrategy to provide a specialized interface for
 * "such that" clauses that involve relationships between two statements.
 *
 */
class StmtStmtStrategy : public SuchThatStrategy {
public:
    ~StmtStmtStrategy() override = default;


    virtual void processIntegerParams(const Token& firstParam, const Token& secondParam,
                              unordered_set<string>& result) = 0;

    virtual void processFirstParam(const Token& secondParam, const string& variant,
                                   unordered_set<string>& result) = 0;

    virtual void processSecondParam(const Token& firstParam, const string& variant,
                            unordered_set<string>& result) = 0;
protected:
    static bool isBothParamsWildcard(const Token& firstParam, const Token& secondParam);
    static bool isBothParamsInteger(const Token& firstParam, const Token& secondParam);
    static void fillResult(const unordered_set<int>& follows, unordered_set<string>& result);


};

