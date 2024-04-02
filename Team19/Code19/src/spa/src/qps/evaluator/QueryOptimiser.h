#pragma once

#include <utility>
#include <vector>
#include <memory>
#include "qps/parser/clauses/Clause.h"
#include "qps/evaluator/QueryGroup.h"

class QueryOptimiser {

public:
    explicit QueryOptimiser(std::vector<std::shared_ptr<Clause>> clauses) {
        this->clauses = std::move(clauses);
    };
    std::vector<std::shared_ptr<QueryGroup>> optimise(bool isOptimised);

private:
    std::vector<std::shared_ptr<Clause>> clauses;
    std::vector<std::shared_ptr<QueryGroup>> createQueryGroups();
    std::shared_ptr<QueryGroup> createSingleQueryGroup();
    std::vector<std::shared_ptr<QueryGroup>> mergeCommonQueryGroups(std::vector<std::shared_ptr<QueryGroup>>& queryGroups);
    std::vector<std::shared_ptr<QueryGroup>> sortQueryGroups(std::vector<std::shared_ptr<QueryGroup>>& queryGroups);



};


