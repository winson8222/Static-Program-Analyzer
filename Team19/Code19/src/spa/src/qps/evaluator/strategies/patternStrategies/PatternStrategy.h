#pragma once

#include "qps/evaluator/QueryEvaluationStrategy.h"

class PatternStrategy : public QueryEvaluationStrategy {
private:



public:
    std::shared_ptr<StatementReader> getStatementReader();


protected:
    std::shared_ptr<StatementReader> statementReader;
    Token relationship;
    virtual void processSynonyms(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) = 0;
    virtual void processQuotedIdent(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) = 0;
    virtual void processWildcard(ParsingResult parsingResult, std::shared_ptr<ResultTable> result) = 0;
    static void insertRowsWithTwoCols(Token firstParam, Token relationship, ParsingResult parsingResult, 
        std::shared_ptr<IControlPatternReader> reader, std::shared_ptr<ResultTable> resultTable);
    void setRelationship(Token relationShip);
};
