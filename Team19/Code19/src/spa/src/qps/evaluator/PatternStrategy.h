#pragma
#define PATTERNSTRATEGY_H

#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"


using namespace std;

class PatternStrategy : public QueryEvaluationStrategy {
private:
    std::shared_ptr<AssignPatternReader> patternReader;
    std::shared_ptr<AssignReader> assignReader;


public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;

    void getMatchedStmtsWithVariable(const Token& firstParam, string secondParamValue, string assignSynonym, std::shared_ptr<ResultTable> result, bool partialMatch);
    void getStatementsByIdent(const string& colName, const Token& firstParam,
                               string expressionValue, std::shared_ptr<ResultTable> result, bool partialMatch);
    void fillSingleColumnResult(const string& colName, const unordered_set<string>& follows, std::shared_ptr<ResultTable> result);
    void fillAssignAndSynonymPairResult(const unordered_set<int>& patternNumbers, const string& assignSynonym, const Token& firstParam, const std::shared_ptr<ResultTable>& result);

};

