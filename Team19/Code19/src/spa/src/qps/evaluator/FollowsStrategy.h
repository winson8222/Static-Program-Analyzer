#pragma
// FollowsStrategy.h
#define FOLLOWSSTRATEGY_H

#include "QueryEvaluationStrategy.h"

using namespace std;

class FollowsStrategy : public QueryEvaluationStrategy {
public:
    unordered_set<string> evaluateQuery(PKBReader& pkbReader, const ParsingResult& parsingResult) override;
};

