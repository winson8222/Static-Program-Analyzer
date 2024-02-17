#pragma
#define PATTERNSTRATEGY_H

#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"


using namespace std;

class PatternStrategy : public StmtStmtStrategy {
private:
    std::shared_ptr<PatternReader> patternReader;
    std::shared_ptr<AssignReader> assignReader;


public:
    unordered_set<string> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;

    void processLHS(const Token& firstParam, unordered_set<string>& result) override;
    void processRHS(const Token& secondParam, unordered_set<string>& result, bool partialMatch) override;
    void combineResults(const unordered_set<string>& newResult, unordered_set<string>& result);

};

