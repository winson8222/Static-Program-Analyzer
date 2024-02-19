#pragma
#define PATTERNSTRATEGY_H

#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"


using namespace std;

class PatternStrategy : public QueryEvaluationStrategy {
private:
    std::shared_ptr<AssignPatternReader> patternReader;
    std::shared_ptr<AssignReader> assignReader;


public:
    unordered_set<string> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;

    void processLHS(const Token& firstParam, unordered_set<string>& result);
    void processRHS(const Token& secondParam, unordered_set<string>& result, bool partialMatch);
    void combineResults(const unordered_set<int>& newResult, unordered_set<string>& result);

    void fillResult(const unordered_set<int>& follows, unordered_set<std::string>& result);

};

