#pragma once

#include <vector>
#include <unordered_set>
#include "qps/parser/clauses/Clause.h"
class QueryGroup {

private:
    std::unordered_set<std::string> commonSynonyms;
    std::vector<std::shared_ptr<Clause>> clauses;

public:
    std::unordered_set<std::string> getCommonSynonyms();
    std::vector<std::shared_ptr<Clause>> getClauses();
    void addCommonSynonym(std::string commonSynonym);
    void setCommonSynonyms(std::unordered_set<std::string> commonSynonyms);
    void setClauses(std::vector<std::shared_ptr<Clause>> clauses);
    void addClause(std::shared_ptr<Clause> clause);
    bool hasCommonSynonym(std::shared_ptr<Clause> clause);
    bool hasCommonSynonymWithGroup(QueryGroup queryGroup);
    void mergeQueryGroup(std::shared_ptr<QueryGroup> queryGroup);

};


