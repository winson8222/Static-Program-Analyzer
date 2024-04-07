#pragma once

#include "qps/parser/Token.h"
#include "qps/evaluator/strategies/suchThatStrategies/SuchThatStrategy.h"

class StmtEntStrategy : public SuchThatStrategy {
private:
    std::shared_ptr<IRelationshipReader<int, std::string>> reader;

public:
	~StmtEntStrategy() override = default;

	void processBothSynonyms(const ParsingResult& parsingResult
		, std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager);
	void processFirstParam(const ParsingResult& parsingResult
		, std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager);
	void processSecondParam(const ParsingResult& parsingResult
		, std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager);
	void processBothConstants(const ParsingResult& parsingResult
		, std::shared_ptr<ResultTable> resultTable);
	static void setTrueIfRelationShipExist(const Token& firstParam, const Token& secondParam,
		const std::shared_ptr<IRelationshipReader<int, std::string>>& reader, std::shared_ptr<ResultTable> resultTable);
    void setReader(std::shared_ptr<IRelationshipReader<int, std::string>> reader);
    std::shared_ptr<IRelationshipReader<int, std::string>> getReader();
};
