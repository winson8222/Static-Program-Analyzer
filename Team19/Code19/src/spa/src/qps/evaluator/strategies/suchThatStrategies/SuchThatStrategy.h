#pragma once

#include "qps/evaluator/QueryEvaluationStrategy.h" // Make sure the path is correct

class SuchThatStrategy : public QueryEvaluationStrategy {
protected:
    virtual void setReader(PKBReaderManager& pkbReaderManager) = 0;
    virtual void addTrueRelationships(std::shared_ptr<ResultTable> result) = 0;

    // Common method to be used by derived classes for optimised evaluation
    std::shared_ptr<ResultTable> evaluateQueryOptimisedCommon(PKBReaderManager &pkbReaderManager,
                                                              const ParsingResult &parsingResult,
                                                              const Clause &clause,
                                                              std::shared_ptr<ResultTable> result) {
        setBothParams(clause);
        setReader(pkbReaderManager);
        setIntermediateResultTable(result);

        std::unordered_set<std::string> allSynonyms = clause.getAllSynonyms();
        if (!hasCommonSynonyms(allSynonyms, result)) {
            return evaluateQuery(pkbReaderManager, parsingResult, clause); // Fallback to standard evaluation
        }

        auto optimisedResultTable = std::make_shared<ResultTable>();
        addTrueRelationships(optimisedResultTable); // Implement this method in the derived classes
        return optimisedResultTable;
    }

public:
    // Inherit the constructors
    SuchThatStrategy() = default;
    virtual ~SuchThatStrategy() = default;

    // Use implementations from the base class
    using QueryEvaluationStrategy::evaluateQuery;
    using QueryEvaluationStrategy::evaluateQueryOptimised;
};
