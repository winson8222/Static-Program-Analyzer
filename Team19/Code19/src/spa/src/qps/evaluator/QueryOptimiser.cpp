#include "QueryOptimiser.h"
#include "map"



#include <iostream>
#include <utility>

std::vector<std::shared_ptr<QueryGroup>> QueryOptimiser::optimise(bool isOptimised) {
    // if isOptimised is False, return a single queryGroup
    if (!isOptimised) {
        std::shared_ptr<QueryGroup> queryGroup = createSingleQueryGroup();
        queryGroup->setClauses(clauses);
        return {queryGroup};
    }
    std::vector<std::shared_ptr<QueryGroup>> queryGroups = createQueryGroups();
    std::vector<std::shared_ptr<QueryGroup>> mergedQueryGroups = mergeCommonQueryGroups(queryGroups);
    mergedQueryGroups = sortQueryGroups(mergedQueryGroups);
    // pass the current queryGroup in the vector to the arrangeByRelatedClausesAndPenalties method and replace the one
    // corresponding index
    for (size_t i = 0; i < mergedQueryGroups.size(); ++i) {
        setRelatedClausesAndPenalties(mergedQueryGroups[i]);
        // set up relationshipsMap and sort the relationshipsMap by penalty
    }
    sortRelationshipsMap();
    for (size_t i = 0; i < mergedQueryGroups.size(); ++i) {
        sortQueryGroup(mergedQueryGroups[i]);
    }
    moveBooleanGroupToFront(mergedQueryGroups);
    return mergedQueryGroups;
}

void QueryOptimiser::sortQueryGroup(std::shared_ptr<QueryGroup> &queryGroup) {
    std::vector<std::shared_ptr<Clause>> sortedClauses = sortByRelatedClauses(queryGroup->getClauses());
    queryGroup->setClauses(sortedClauses);
}


std::shared_ptr<QueryGroup> QueryOptimiser::createSingleQueryGroup() {
    return std::make_shared<QueryGroup>();
}

std::vector<std::shared_ptr<QueryGroup>> QueryOptimiser::mergeCommonQueryGroups(std::vector<std::shared_ptr<QueryGroup>>& queryGroups) {
    if (queryGroups.size() <= 1) {
        return queryGroups;
    }

    bool hasMerged = true;
    while (hasMerged) {
        hasMerged = false;
        for (size_t i = 0; i < queryGroups.size() - 1 && !hasMerged; ++i) {
            for (size_t j = i + 1; j < queryGroups.size() && !hasMerged; ++j) {
                bool foundCommonSynonym = false;
                const auto& iSynonyms = queryGroups[i]->getCommonSynonyms();
                const auto& jSynonyms = queryGroups[j]->getCommonSynonyms();

                // Iterate through each synonym in j's group and check if it exists in i's group
                for (const auto& synonym : jSynonyms) {
                    if (iSynonyms.find(synonym) != iSynonyms.end()) {
                        foundCommonSynonym = true;
                        break; // Found a common synonym, no need to continue
                    }
                }

                if (foundCommonSynonym) {
                    queryGroups[i]->mergeQueryGroup(queryGroups[j]);
                    queryGroups.erase(queryGroups.begin() + j);
                    hasMerged = true;
                    // Since we've modified the vector, it's safer to restart the loop or exit if required.
                    // However, as per your comment, if the logic needs to continue checking, adjust accordingly.
                }

            }
        }
    }

    return queryGroups;
}



std::vector<std::shared_ptr<QueryGroup>> QueryOptimiser::createQueryGroups() {
    std::vector<std::shared_ptr<QueryGroup>> queryGroups;
    std::unordered_map<int, std::unordered_set<std::string>> queryGroupMap;

    for (const auto& clause : clauses) {
        auto querySynonyms = clause->getAllSynonyms();
        bool isFound = false;

        for (auto &[index, commonSynonyms] : queryGroupMap) {
            if (index >= queryGroups.size()) {
                continue;
            }

            // Check if synonyms sets are empty or have common elements.
            bool shouldMerge = commonSynonyms.empty() && querySynonyms.empty();
            if (!shouldMerge) {
                for (const auto &synonym : querySynonyms) {
                    if (commonSynonyms.find(synonym) != commonSynonyms.end()) {
                        shouldMerge = true;
                        break;
                    }
                }
            }

            if (shouldMerge) {
                queryGroups[index]->addClause(clause);
                commonSynonyms.insert(querySynonyms.begin(), querySynonyms.end());
                isFound = true;
                break;
            }
        }

        if (!isFound) {
            auto newQueryGroup = std::make_shared<QueryGroup>();
            newQueryGroup->addClause(clause);
            queryGroups.push_back(newQueryGroup);
            queryGroupMap[queryGroups.size() - 1] = newQueryGroup->getCommonSynonyms();
        }
    }
    return queryGroups;
}

std::vector<std::shared_ptr<QueryGroup>> QueryOptimiser::sortQueryGroups(
        std::vector<std::shared_ptr<QueryGroup>> &queryGroups) {
    // sort them by the number of clauses they have, more the clauses, the higher the priority
    std::sort(queryGroups.begin(), queryGroups.end(),
              [](const std::shared_ptr<QueryGroup>& a, const std::shared_ptr<QueryGroup>& b) {
                  return a->getClauses().size() > b->getClauses().size();
              });

    return queryGroups;
}

void QueryOptimiser::setRelatedClausesAndPenalties(std::shared_ptr<QueryGroup> &queryGroup) {
    for (const auto& clause : queryGroup->getClauses()) {
        // Check if clause is related to any other clause in the group
        std::unordered_set<std::string> allSynonyms = clause->getAllSynonyms();
        for (std::string synonym : allSynonyms) {
            insertIntoRelationshipsMap(synonym, clause);
        }
    }
}

bool QueryOptimiser::comparePenalty(const std::shared_ptr<Clause> &a, const std::shared_ptr<Clause> &b) {
    return a->getPenalty() < b->getPenalty();
}

void QueryOptimiser::sortRelationshipsMap() {
    for (auto& [synonym, currentClauses] : relationshipsMap) {
        std::sort(currentClauses.begin(), currentClauses.end(),
                  comparePenalty);
    }
}

void QueryOptimiser::addRelatedClausesIfExists(std::string synonym, std::unordered_set<std::shared_ptr<Clause>>& addedClauses, std::vector<std::shared_ptr<Clause>>& sortedClauses) {
    if (relationshipsMap.find(synonym) != relationshipsMap.end()) {
        for (const std::shared_ptr<Clause> relatedClause: relationshipsMap[synonym]) {
            if (addedClauses.find(relatedClause) == addedClauses.end()) {
                addedClauses.insert(relatedClause);
                sortedClauses.push_back(relatedClause);
                // related clauses into the sorted clauses
            }
        }
    }
}

std::vector<std::shared_ptr<Clause>> QueryOptimiser::sortByRelatedClauses(const std::vector<std::shared_ptr<Clause>> &clauses) {
    std::unordered_set<std::shared_ptr<Clause>> addedClauses;
    std::vector<std::shared_ptr<Clause>> sortedClauses;
    std::vector<std::shared_ptr<Clause>> preSortedClauses = clauses;
    std::sort(preSortedClauses.begin(), preSortedClauses.end(), comparePenalty);
    for (const std::shared_ptr<Clause> clause : preSortedClauses) {
        if (addedClauses.find(clause) == addedClauses.end()) {
            addedClauses.insert(clause);
            sortedClauses.push_back(clause);
        }


        std::unordered_set<std::string> allSynonyms = clause->getAllSynonyms();
        for (std::string synonym : allSynonyms) {
            addRelatedClausesIfExists(synonym, addedClauses, sortedClauses);
        }
    }

    // move all nextT and affectT clauses to the end of the sorted clauses
    std::vector<std::shared_ptr<Clause>> highPenaltyClauses;
    for (const std::shared_ptr<Clause> clause : preSortedClauses) {
        Token relationshipToken = clause->getRelationship();
        TokenType relationshipType = relationshipToken.getType();
        if (relationshipType == TokenType::NextT || relationshipType == TokenType::Affects) {
            highPenaltyClauses.push_back(clause);
            sortedClauses.erase(std::remove(sortedClauses.begin(), sortedClauses.end(), clause), sortedClauses.end());
        }
    }

    std::sort(highPenaltyClauses.begin(), highPenaltyClauses.end(), comparePenalty);
    sortedClauses.insert(sortedClauses.end(), highPenaltyClauses.begin(), highPenaltyClauses.end());
    return sortedClauses;
}


void QueryOptimiser::insertIntoRelationshipsMap(std::string relatedSynonym, std::shared_ptr<Clause> clause) {
    if (relationshipsMap.find(relatedSynonym) == relationshipsMap.end()) {
        std::vector<std::shared_ptr<Clause>> newClausesSet = {clause};
        relationshipsMap[relatedSynonym] = newClausesSet;
    } else {
        auto it = relationshipsMap.find(relatedSynonym);
        it->second.push_back(clause);
    }

}

void QueryOptimiser::moveBooleanGroupToFront(std::vector<std::shared_ptr<QueryGroup>> &queryGroups) {
    std::stable_partition(queryGroups.begin(), queryGroups.end(),
                          [](const std::shared_ptr<QueryGroup>& group) {
                              return group->getCommonSynonyms().empty();
                          });

}