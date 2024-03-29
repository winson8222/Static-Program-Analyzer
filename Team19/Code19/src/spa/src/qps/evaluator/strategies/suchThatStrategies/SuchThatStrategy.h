#pragma once

#include "qps/evaluator/QueryEvaluationStrategy.h"

using namespace std;
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
};
