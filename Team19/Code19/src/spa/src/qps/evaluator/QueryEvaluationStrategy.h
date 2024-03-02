// QueryEvaluationStrategy.h
#ifndef QUERYEVALUATIONSTRATEGY_H
#define QUERYEVALUATIONSTRATEGY_H

#include <unordered_set>
#include <string>
#include "qps/parser/ParsingResult.h" // Include your ParsingResult header
#include "pkb/PKBReaderManager.h" // Include your PKBReader header
#include "qps/evaluator/ResultTable.h"


class QueryEvaluationStrategy {
public:
    virtual std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) = 0;
    virtual ~QueryEvaluationStrategy() = default;

protected:
    static void convertIntSetToStringSet(const std::unordered_set<int>& intSet, std::unordered_set<std::string>& stringSet);
    static string extractQuotedExpression(const Token& token);
    static bool isBothParamsWildcard(const Token& firstParam, const Token& secondParam);
    static unordered_set<int> combineFoundStatements(const unordered_set<int>& newResult, const unordered_set<int>& result);
    static unordered_set<int> getFilteredStmtsNumByType(unordered_set<int> allStatements, string stmtType, PKBReaderManager pkbReaderManager);

};

#endif //QUERYEVALUATIONSTRATEGY_H
