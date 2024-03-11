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

public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;

    void processSynonyms(const Token& firstParam, const Token& secondParam,
        const string& variant, std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager);
    void processFirstParam(const Token& firstParam, const Token& secondParam, const string& variant,
        std::shared_ptr<ResultTable> resultTable,const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) override;
    void processSecondParam(const Token& firstParam, const Token& secondParam, const string& variant,
        std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) override;
    void processIntegerParams(const Token& firstParam, const Token& secondParam,
        std::shared_ptr<ResultTable> resultTable) override;

};
