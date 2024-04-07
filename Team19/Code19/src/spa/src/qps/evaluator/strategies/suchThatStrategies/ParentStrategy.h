#pragma once

#include <iostream>
#include "qps/evaluator/strategies/suchThatStrategies/StmtStmtStrategy.h"
#include "qps/parser/Token.h" 

class ParentStrategy : public StmtStmtStrategy {
private:

    std::string variant;

public:
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager &pkbReaderManager, const ParsingResult &parsingResult, const Clause &clause) override;
    std::shared_ptr<ResultTable>
    evaluateQueryOptimised(PKBReaderManager &pkbReaderManager, const ParsingResult &parsingResult, const Clause &clause,
                           std::shared_ptr<ResultTable> result) override;

};
