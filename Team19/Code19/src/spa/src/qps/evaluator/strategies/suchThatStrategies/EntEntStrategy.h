#pragma once

#include "qps/evaluator/strategies/suchThatStrategies/SuchThatStrategy.h"

class EntEntStrategy : public SuchThatStrategy {

public:
	~EntEntStrategy() override = default;

	virtual void processBothSynonyms(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable) = 0;
	virtual void processFirstParam(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable) = 0;
	virtual void processSecondParam(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable) = 0;
	virtual void processBothConstants(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable) = 0;
	static void setTrueIfRelationShipExist(const Token& firstParam, const Token& secondParam,
		const std::shared_ptr<IRelationshipReader<std::string, std::string> >& reader, std::shared_ptr<ResultTable> resultTable);

};
