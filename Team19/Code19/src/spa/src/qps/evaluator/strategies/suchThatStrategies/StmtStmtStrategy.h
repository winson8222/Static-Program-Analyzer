#pragma once

#include "qps/evaluator/strategies/suchThatStrategies/SuchThatStrategy.h"

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
    static void setTrueIfRelationShipExist(const Token &firstParam, const Token &secondParam,
                                           const std::shared_ptr<IRelationshipReader<int, int>> &reader,
                                           std::shared_ptr<ResultTable> resultTable);
    static void insertRowsWithTwoCols(const Token &firstParam, const Token &secondParam, std::shared_ptr<IRelationshipReader<int ,int>> reader,
                                      const ParsingResult &parsingResult, std::shared_ptr<ResultTable> resultTable, PKBReaderManager &pkbReaderManager);


};
