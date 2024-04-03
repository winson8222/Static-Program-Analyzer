#include "qps/evaluator/QueryGroup.h"


std::unordered_set<std::string> QueryGroup::getCommonSynonyms() {
    return commonSynonyms;
}

std::vector<std::shared_ptr<Clause>> QueryGroup::getClauses() {
    return clauses;
}

void QueryGroup::addCommonSynonym(std::string commonSynonym) {
    commonSynonyms.insert(commonSynonym);
}

void QueryGroup::addClause(std::shared_ptr<Clause> clause) {
    clauses.push_back(clause);
    std::unordered_set<std::string> clauseSynonyms = clause->getAllSynonyms();
    for (const std::string& synonym : clauseSynonyms) {
        commonSynonyms.insert(synonym);
    }
}

bool QueryGroup::hasCommonSynonym(std::shared_ptr<Clause> clause) {
    std::unordered_set<std::string> clauseSynonyms = clause->getAllSynonyms();
    for (auto synonym : clauseSynonyms) {
        if (commonSynonyms.find(synonym) != commonSynonyms.end()) {
            return true;
        }
    }
    return false;
}

bool QueryGroup::hasCommonSynonymWithGroup(QueryGroup queryGroup) {
    std::unordered_set<std::string> groupSynonyms = queryGroup.getCommonSynonyms();
    for (auto synonym : groupSynonyms) {
        if (commonSynonyms.find(synonym) != commonSynonyms.end()) {
            return true;
        }
    }
    return false;
}

void QueryGroup::mergeQueryGroup(std::shared_ptr<QueryGroup> queryGroup) {
    // merge the common synonyms
    std::unordered_set<std::string> groupSynonyms = queryGroup->getCommonSynonyms();
    for (const std::string& synonym : groupSynonyms) {
        commonSynonyms.insert(synonym);
    }
    // merge the clauses
    std::vector<std::shared_ptr<Clause>> groupClauses = queryGroup->getClauses();
    for (const std::shared_ptr<Clause>& clause : groupClauses) {
        clauses.push_back(clause);
    }
}

void QueryGroup::setCommonSynonyms(std::unordered_set<std::string> commonSynonyms) {
    this->commonSynonyms = commonSynonyms;
}

void QueryGroup::setClauses(std::vector<std::shared_ptr<Clause>> clauses) {
    this->clauses = std::move(clauses);
}