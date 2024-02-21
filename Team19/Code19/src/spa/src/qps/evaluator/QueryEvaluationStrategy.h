// QueryEvaluationStrategy.h
#ifndef QUERYEVALUATIONSTRATEGY_H
#define QUERYEVALUATIONSTRATEGY_H

#include <unordered_set>
#include <string>
#include "../Parser/ParsingResult.h" // Include your ParsingResult header
#include "../../pkb/PKBReaderManager.h" // Include your PKBReader header
#include "qps/evaluator/ResultTable.h"


class QueryEvaluationStrategy {
public:
    virtual std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) = 0;
    virtual ~QueryEvaluationStrategy() = default;

protected:
    static void convertIntSetToStringSet(const std::unordered_set<int>& intSet, std::unordered_set<std::string>& stringSet);
    static string extractQuotedExpression(const Token& token);
    static bool isBothParamsWildcard(const Token& firstParam, const Token& secondParam);
};

#endif //QUERYEVALUATIONSTRATEGY_H
