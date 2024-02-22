#pragma
#define PATTERNSTRATEGY_H

#include "qps/evaluator/suchThatStrategies/StmtStmtStrategy.h"


using namespace std;

class PatternStrategy : public QueryEvaluationStrategy {
private:
    std::shared_ptr<AssignPatternReader> patternReader;
    std::shared_ptr<AssignReader> assignReader;
    std::shared_ptr<IfPatternReader> ifPatternReader; // Handles patterns for if statements
    std::shared_ptr<WhilePatternReader> whilePatternReader; // Handles patterns for while statements

public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult) override;

    void getMatchedStmtsWithVariable(const Token& firstParam, string secondParamValue, string assignSynonym, std::shared_ptr<ResultTable> result, bool partialMatch);
    void getStatementsByIdent(const string& colName, const Token& firstParam,
                               string expressionValue, std::shared_ptr<ResultTable> result, bool partialMatch);
    void fillSingleColumnResult(const string& colName, const unordered_set<string>& follows, std::shared_ptr<ResultTable> result);
    void fillAssignAndSynonymPairResult(const unordered_set<int>& patternNumbers, const string& assignSynonym, const Token& firstParam, const std::shared_ptr<ResultTable>& result);
    void getAllStatementsByRHS(string patternSynonym , string expressionValue, std::shared_ptr<ResultTable> result);
    // Method to handle 'if' patterns
    void handleIfPatterns(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> result);

    // Method to handle 'while' patterns
    void handleWhilePatterns(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> result);

    // Determines the pattern type and delegates processing
    void processPatternType(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> result);
};

