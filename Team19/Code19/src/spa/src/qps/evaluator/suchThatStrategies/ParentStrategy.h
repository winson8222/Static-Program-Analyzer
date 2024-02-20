#pragma
// FollowsStrategy.h
#define FOLLOWSSTRATEGY_H

#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"


using namespace std;

class ParentStrategy : public StmtStmtStrategy {
private:
    std::shared_ptr<ParentReader> parentReader;
    std::shared_ptr<ParentTReader> parentTTReader;
    std::shared_ptr<StatementReader> statementReader;

public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;

    void processFirstParam(const Token& secondParam, const string& variant,
                           unordered_set<string>& result) override;
    void processSecondParam(const Token& firstParam, const string& variant,
                            unordered_set<string>& result) override;
    void processIntegerParams(const Token& firstParam, const Token& secondParam,
                              unordered_set<string>& result) override;
};
