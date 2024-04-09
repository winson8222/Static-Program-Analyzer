#pragma once

#include "qps/evaluator/QueryEvaluationStrategy.h"

/**
 * @brief Base class for implementing evaluation strategies for "such that" clauses in queries.
 *
 * This class provides a common interface and foundational behavior for all "such that"
 * clauses within the query processing system. Derived classes should implement specific
 * evaluation strategies for different types of "such that" clauses, providing the logic
 * necessary to evaluate those clauses against the program knowledge base.
 *
 */
class SuchThatStrategy : public QueryEvaluationStrategy {

public:
    SuchThatStrategy() = default;

protected:
    void addTrueRelationshipsInResultTable(std::shared_ptr<ResultTable> newResultTable);
    void addTrueLeftSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager);
    void addTrueRightSynonymInResultTable(std::shared_ptr<ResultTable> newResultTable, const ParsingResult& parsingResult,PKBReaderManager& pkbReaderManager);
    virtual void addToListIfKeyRelationshipExists( const std::unordered_set<std::string>& values,
                                           std::vector<std::string>& filteredValues,
                                           const Token& comparisonToken) = 0;

    virtual void addToListIfValueRelationshipExists( const std::unordered_set<std::string>& values,
                                             std::vector<std::string>& filteredValues,
                                             const Token& comparisonToken) = 0;

    virtual void addToListIfRelationshipExistsWithItself(
            const std::unordered_set<std::string>& values,
            std::vector<std::string>& filteredValues) = 0;

    virtual void addToListIfValueExists(
            const std::unordered_set<std::string>& values,
            std::vector<std::string>& filteredValues) = 0;

    virtual void addToListIfKeyExists(
            const std::unordered_set<std::string>& values,
            std::vector<std::string>& filteredValues) = 0;

    virtual void addPairsToListsByKey(
            const std::unordered_set<std::string>& sourceValues,
            const std::string& type,
            PKBReaderManager& pkbReaderManager,
            std::vector<std::string>& firstList,
            std::vector<std::string>& secondList) = 0;

    virtual void addPairsToListsByValue(
            const std::unordered_set<std::string>& sourceValues,
            const std::string& type,
            PKBReaderManager& pkbReaderManager,
            std::vector<std::string>& firstList,
            std::vector<std::string>& secondList) = 0;

    virtual void addPairIfRelationshipExists(
            const std::unordered_set<std::string>& sourceValues,
            const std::unordered_set<std::string>& targetValues,
            std::vector<std::string>& sourceList,
            std::vector<std::string>& targetList) = 0;




};
