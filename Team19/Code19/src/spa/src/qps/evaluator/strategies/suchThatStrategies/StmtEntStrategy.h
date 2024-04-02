#pragma once

#include "qps/parser/Token.h"
#include "qps/evaluator/strategies/suchThatStrategies/SuchThatStrategy.h"

class StmtEntStrategy : public SuchThatStrategy {

public:
	~StmtEntStrategy() override = default;

	virtual void processBothSynonyms(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
		, std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) = 0;
	virtual void processFirstParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
		, std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) = 0;
	virtual void processSecondParam(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
		, std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager) = 0;
	virtual void processBothConstants(const Token& firstParam, const Token& secondParam, const ParsingResult& parsingResult
		, std::shared_ptr<ResultTable> resultTable) = 0;
	static void setTrueIfRelationShipExist(const Token& firstParam, const Token& secondParam,
		const std::shared_ptr<IRelationshipReader<int, std::string>>& reader, std::shared_ptr<ResultTable> resultTable);
};
