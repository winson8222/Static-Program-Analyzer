#pragma
// FollowsStrategy.h
#define FOLLOWSSTRATEGY_H

#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"


using namespace std;

class FollowsStrategy : public StmtStmtStrategy {
private:
    std::shared_ptr<FollowsReader> followsReader;
    std::shared_ptr<FollowsTReader> followsTReader;
    std::shared_ptr<StatementReader> statementReader;

public:
    unordered_set<string> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;

        void processFirstParam(const Token& secondParam, const string& variant,
        unordered_set<string>& result) override;
        void processSecondParam(const Token& firstParam, const string& variant,
        unordered_set<string>& result) override;
        void processIntegerParams(const Token& firstParam, const Token& secondParam,
        unordered_set<string>& result) override;
};

