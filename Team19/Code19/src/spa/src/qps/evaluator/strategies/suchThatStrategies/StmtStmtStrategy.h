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


protected:
	static bool isBothParamsInteger(const Token& firstParam, const Token& secondParam);
	static void setTrueIfRelationShipExist(const Token& firstParam, const Token& secondParam, 
		const std::shared_ptr<IRelationshipReader<int, int>>& reader, std::shared_ptr<ResultTable> resultTable);
	static void insertRowsWithTwoCols(const Token& firstParam, const Token& secondParam, std::shared_ptr<IRelationshipReader<int, int>> reader,
		const ParsingResult& parsingResult, std::shared_ptr<ResultTable> resultTable, PKBReaderManager& pkbReaderManager);
    void setReader(const std::shared_ptr<IRelationshipReader<int, int>>& reader);
    void processSynonyms(std::shared_ptr<ResultTable> resultTable, const ParsingResult &parsingResult,
                         PKBReaderManager &pkbReaderManager);

    void processIntegerParams(std::shared_ptr<ResultTable> resultTable);

    void processFirstParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager);

    void processSecondParam(std::shared_ptr<ResultTable> resultTable, const ParsingResult& parsingResult, PKBReaderManager& pkbReaderManager);

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

