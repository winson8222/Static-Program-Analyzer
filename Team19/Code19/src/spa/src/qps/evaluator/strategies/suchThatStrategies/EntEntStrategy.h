#pragma once

#include "qps/evaluator/strategies/suchThatStrategies/SuchThatStrategy.h"

class EntEntStrategy : public SuchThatStrategy {
private:
    std::shared_ptr<IRelationshipReader<std::string, std::string>> reader;

public:
	~EntEntStrategy() override = default;
    std::shared_ptr<ResultTable> getEvaluatedResultTable(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable) override;
	void processBothSynonyms(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable);
	void processFirstParam(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable);
	void processSecondParam(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable);
	void processBothConstants(const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable);
	static void setTrueIfRelationShipExist(const Token& firstParam, const Token& secondParam,
		const std::shared_ptr<IRelationshipReader<std::string, std::string> >& reader, std::shared_ptr<ResultTable> resultTable);
    void setReader(const std::shared_ptr<IRelationshipReader<std::string, std::string>>& reader);
    std::shared_ptr<IRelationshipReader<std::string, std::string>> getReader();
    void addToListIfKeyRelationshipExists( const std::unordered_set<std::string>& values,
                                           std::vector<std::string>& filteredValues,
                                           const Token& comparisonToken) override;

    void addToListIfValueRelationshipExists(const std::unordered_set<std::string>& values,
                                            std::vector<std::string>& filteredValues,
                                            const Token& comparisonToken) override;

    void addToListIfRelationshipExistsWithItself(
            const std::unordered_set<std::string>& values,
            std::vector<std::string>& filteredValues) override;

    void addToListIfValueExists(
            const std::unordered_set<std::string>& values,
            std::vector<std::string>& filteredValues) override;

    void addToListIfKeyExists(
            const std::unordered_set<std::string>& values,
            std::vector<std::string>& filteredValues) override;

    void addPairsToListsByKey(
            const std::unordered_set<std::string>& sourceValues,
            const std::string& type,
            PKBReaderManager& pkbReaderManager,
            std::vector<std::string>& firstList,
            std::vector<std::string>& secondList) override;

    void addPairsToListsByValue(
            const std::unordered_set<std::string>& sourceValues,
            const std::string& type,
            PKBReaderManager& pkbReaderManager,
            std::vector<std::string>& firstList,
            std::vector<std::string>& secondList) override;

    void addPairIfRelationshipExists(
            const std::unordered_set<std::string>& sourceValues,
            const std::unordered_set<std::string>& targetValues,
            std::vector<std::string>& sourceList,
            std::vector<std::string>& targetList) override;
};
