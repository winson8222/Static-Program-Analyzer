#pragma once

#include <iostream>
#include "qps/evaluator/strategies/suchThatStrategies/StmtStmtStrategy.h"
#include "qps/parser/Token.h" 

class ParentStrategy : public StmtStmtStrategy {
private:
    std::shared_ptr<IRelationshipReader<int ,int>> reader;
    std::shared_ptr<StatementReader> statementReader;
    Token firstParam;
    Token secondParam;
    std::string variant;

public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;
    std::shared_ptr<ResultTable> evaluateQueryOptimised(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, std::shared_ptr<ResultTable> result) override;
    void processSynonyms(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager);
    void processFirstParam(std::shared_ptr<ResultTable> resultTable,const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) override;
    void processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager) override;
    void processIntegerParams(std::shared_ptr<ResultTable> resultTable) override;
};
