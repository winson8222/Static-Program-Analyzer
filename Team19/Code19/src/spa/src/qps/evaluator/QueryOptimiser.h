#pragma once

#include <utility>
#include <vector>
#include <memory>
#include "qps/parser/clauses/Clause.h"
#include "qps/evaluator/QueryGroup.h"
#include "unordered_set"
#include "unordered_map"
#include "algorithm"

class QueryOptimiser {

public:
    explicit QueryOptimiser(std::vector<std::shared_ptr<Clause>> clauses) {
        this->clauses = std::move(clauses);
    };
    std::vector<std::shared_ptr<QueryGroup>> optimise(bool isOptimised);


private:
    std::vector<std::shared_ptr<Clause>> clauses;
    std::unordered_map<std::string, std::vector<std::shared_ptr<Clause>>> relationshipsMap;
    std::vector<std::shared_ptr<QueryGroup>> createQueryGroups();
    std::shared_ptr<QueryGroup> createSingleQueryGroup();
    std::vector<std::shared_ptr<QueryGroup>> mergeCommonQueryGroups(std::vector<std::shared_ptr<QueryGroup>>& queryGroups);
    std::vector<std::shared_ptr<QueryGroup>> sortQueryGroups(std::vector<std::shared_ptr<QueryGroup>>& queryGroups);
    void setRelatedClausesAndPenalties(std::shared_ptr<QueryGroup>& queryGroup);
    void insertIntoRelationshipsMap(std::string relatedSynonym, std::shared_ptr<Clause> clause);
    std::vector<std::shared_ptr<Clause>> sortByRelatedClauses(const std::vector<std::shared_ptr<Clause>> &clauses);
    void sortQueryGroup(std::shared_ptr<QueryGroup>& queryGroup);
    static bool comparePenalty(const std::shared_ptr<Clause>& a, const std::shared_ptr<Clause>& b);
    void addRelatedClausesIfExists(std::string synonym, std::unordered_set<std::shared_ptr<Clause>>& addedClauses, std::vector<std::shared_ptr<Clause>>& sortedClauses);
    void moveBooleanGroupToFront(std::vector<std::shared_ptr<QueryGroup>>& queryGroups);
    void sortAllClauses();



};


