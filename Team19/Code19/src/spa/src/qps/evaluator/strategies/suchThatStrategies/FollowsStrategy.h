#pragma once // Ensures the file is included only once during compilation

#include <string>
#include <unordered_set>
#include <iostream>
#include <memory> 
#include "qps/evaluator/strategies/suchThatStrategies/StmtStmtStrategy.h"
#include "qps/parser/Token.h" 

/**
 * @file FollowsStrategy.h
 * @brief Defines the FollowsStrategy class that implements evaluation for Follows and Follows* relationships.
 *
 * The FollowsStrategy class extends StmtStmtStrategy to evaluate queries related to the Follows and Follows*
 * relationships between statements in a program. It supports handling different types of parameters including
 * statement numbers, statement synonyms, and wildcards.
 */

class FollowsStrategy : public StmtStmtStrategy {
private:
    std::string variant;

public:
    /**
     * Evaluates a query based on the Follows or Follows* relationship.
     * @param pkbReaderManager Reference to the PKB reader manager for accessing program knowledge.
     * @param parsingResult The parsing result containing the details of the query.
     * @return A shared pointer to the result table generated by the evaluation.
     */
    std::shared_ptr<ResultTable> evaluateQuery(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause) override;


    std::shared_ptr<ResultTable> evaluateQueryOptimised(PKBReaderManager& pkbReaderManager, const ParsingResult& parsingResult, const Clause& clause, std::shared_ptr<ResultTable> result) override;
};
