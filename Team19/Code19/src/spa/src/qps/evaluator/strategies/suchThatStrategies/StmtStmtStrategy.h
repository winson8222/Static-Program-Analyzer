#pragma once

#include "qps/evaluator/strategies/suchThatStrategies/SuchThatStrategy.h"

/**
 * @brief Strategy class for evaluating "such that" clauses involving relationships between statements.
 *
 * This class extends the SuchThatStrategy to provide a specialized interface for
 * "such that" clauses that involve relationships between two statements.
 *
 */
class StmtStmtStrategy : public SuchThatStrategy {

private:
    std::shared_ptr<IRelationshipReader<int, int>> reader;
public:
	~StmtStmtStrategy() override = default;

    void processSynonyms(std::shared_ptr<ResultTable> resultTable, const ParsingResult &parsingResult,
                         PKBReaderManager &pkbReaderManager);

	void processIntegerParams(std::shared_ptr<ResultTable> resultTable);

	void processFirstParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager);

	void processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager);
protected:
	static bool isBothParamsInteger(const Token& firstParam, const Token& secondParam);
	static void setTrueIfRelationShipExist(const Token& firstParam, const Token& secondParam, 
		const std::shared_ptr<IRelationshipReader<int, int>>& reader, std::shared_ptr<ResultTable> resultTable);
	static void insertRowsWithTwoCols(const Token& firstParam, const Token& secondParam, std::shared_ptr<IRelationshipReader<int, int>> reader,
		const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager);
    void setReader(const std::shared_ptr<IRelationshipReader<int, int>>& reader);
    std::shared_ptr<IRelationshipReader<int, int>> getReader();
};
