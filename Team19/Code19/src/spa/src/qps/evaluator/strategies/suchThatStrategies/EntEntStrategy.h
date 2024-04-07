#pragma once

#include "qps/evaluator/strategies/suchThatStrategies/SuchThatStrategy.h"

class EntEntStrategy : public SuchThatStrategy {
private:
    std::shared_ptr<IRelationshipReader<std::string, std::string>> reader;

public:
	~EntEntStrategy() override = default;

	void processBothSynonyms(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable);
	void processFirstParam(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable);
	void processSecondParam(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable);
	void processBothConstants(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable);
	static void setTrueIfRelationShipExist(const Token& firstParam, const Token& secondParam,
		const std::shared_ptr<IRelationshipReader<std::string, std::string> >& reader, std::shared_ptr<ResultTable> resultTable);
    void setReader(const std::shared_ptr<IRelationshipReader<std::string, std::string>>& reader);
    std::shared_ptr<IRelationshipReader<std::string, std::string>> getReader();

};
