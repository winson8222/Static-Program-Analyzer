#pragma once

#include "qps/evaluator/QueryEvaluationStrategy.h"


using namespace std;

class PatternStrategy : public QueryEvaluationStrategy {
private:
    std::shared_ptr<StatementReader> statementReader;


public:
    std::shared_ptr<StatementReader> getStatementReader();

    virtual void processSynonyms(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) = 0;
    virtual void processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) = 0;
    virtual void processWildcard(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) = 0;
};

