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
    return mergedQueryGroups;
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