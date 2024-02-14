#pragma
// FollowsStrategy.h
#define FOLLOWSSTRATEGY_H

#include "QueryEvaluationStrategy.h"

using namespace std;

class FollowsStrategy : public QueryEvaluationStrategy {
public:
    unordered_set<string> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;
    void fillResult(const unordered_set<int>& follows, unordered_set<string>& result);
    void FollowsStrategy::processFirstParam(const Token& secondParam, const string& variant,
        shared_ptr<FollowsReader> followsReader,
        shared_ptr<FollowsTReader> followsTReader,
        unordered_set<string>& result);
    void FollowsStrategy::processSecondParam(const Token& firstParam, const string& variant,
        shared_ptr<FollowsReader> followsReader,
        shared_ptr<FollowsTReader> followsTReader,
        unordered_set<string>& result);
    bool FollowsStrategy::isBothParamsWildcard(const Token& firstParam, const Token& secondParam);
    bool FollowsStrategy::isBothParamsInteger(const Token& firstParam, const Token& secondParam);
    void FollowsStrategy::processIntegerParams(const Token& firstParam, const Token& secondParam,
        shared_ptr<FollowsReader> followsReader,
        shared_ptr<StatementReader> statementReader,
        unordered_set<string>& result);
};

