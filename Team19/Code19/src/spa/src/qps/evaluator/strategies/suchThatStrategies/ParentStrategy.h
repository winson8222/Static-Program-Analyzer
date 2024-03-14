#pragma once
// FollowsStrategy.h
#define FOLLOWSSTRATEGY_H

#include "StmtStmtStrategy.h"


using namespace std;

class ParentStrategy : public StmtStmtStrategy {
private:
    std::shared_ptr<ParentReader> parentReader;
    std::shared_ptr<ParentTReader> parentTTReader;
    std::shared_ptr<StatementReader> statementReader;
    Token firstParam;
    Token secondParam;
    string variant;

public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;

    void processSynonyms(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager);
    void processFirstParam(std::shared_ptr<ResultTable> resultTable,const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) override;
    void processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) override;
    void processIntegerParams(std::shared_ptr<ResultTable> resultTable) override;

};
