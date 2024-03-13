#pragma once


#include "SuchThatStrategy.h"

using namespace std;
/**
 * @brief Strategy class for evaluating "such that" clauses involving relationships between statements.
 *
 * This class extends the SuchThatStrategy to provide a specialized interface for
 * "such that" clauses that involve relationships between two statements.
 *
 */
class StmtStmtStrategy : public SuchThatStrategy {
public:
    ~StmtStmtStrategy() override = default;


    virtual void processIntegerParams(std::shared_ptr<ResultTable> resultTable) = 0;

    virtual void processFirstParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) = 0;

    virtual void processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager) = 0;
protected:
    static bool isBothParamsInteger(const Token& firstParam, const Token& secondParam);



};

