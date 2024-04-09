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

    void addTrueRelationshipsInResultTable(std::shared_ptr<ResultTable> newResultTable);
    void addTrueLeftSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager);
    void addTrueRightSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager);
    void addToListIfKeyRelationshipExists( const std::unordered_set<std::string>& values,
                                           std::vector<std::string>& filteredValues,
                                           const Token& comparisonToken);

    void addToListIfValueRelationshipExists( const std::unordered_set<std::string>& values,
                                             std::vector<std::string>& filteredValues,
                                             const Token& comparisonToken);

    void addToListIfRelationshipExistsWithItself(
            const std::unordered_set<std::string>& values,
            std::vector<std::string>& filteredValues);

    void addToListIfValueExists(
            const std::unordered_set<std::string>& values,
            std::vector<std::string>& filteredValues);

    void addToListIfKeyExists(
            const std::unordered_set<std::string>& values,
            std::vector<std::string>& filteredValues);

    void addPairsToListsByKey(
            const std::unordered_set<std::string>& sourceValues,
            const std::string& type,
            PKBReaderManager& pkbReaderManager,
            std::vector<std::string>& firstList,
            std::vector<std::string>& secondList);

    void addPairsToListsByValue(
            const std::unordered_set<std::string>& sourceValues,
            const std::string& type,
            PKBReaderManager& pkbReaderManager,
            std::vector<std::string>& firstList,
            std::vector<std::string>& secondList);

    void addPairIfRelationshipExists(
            const std::unordered_set<std::string>& sourceValues,
            const std::unordered_set<std::string>& targetValues,
            std::vector<std::string>& sourceList,
            std::vector<std::string>& targetList);
};
