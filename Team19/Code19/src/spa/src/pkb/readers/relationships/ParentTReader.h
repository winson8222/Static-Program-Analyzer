#pragma once

#include <memory>

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/ParentTStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ParentTReader: public IRelationshipReader<int, int> {
private:
    std::shared_ptr<ParentTStore> parentTStore;
public:
    ParentTReader(std::shared_ptr<ParentTStore> store);
    // Custom methods
    /**
     * @brief Gets the parentT statement numbers of all "ParentT" relationships.
     * @return unordered_set<int>: The set of statement numbers of s1 in ParentT(s1, s2)
     */
    std::unordered_set<int> getAllParentTs();

    /**
     * @brief Gets the childT statement numbers of all "ParentT" relationships.
     * @return unordered_set<int>: The set of statement numbers of s2 in ParentT(s1, s2)
     */
    std::unordered_set<int> getAllChildrenT();

    /**
     * @brief Gets the set of statement numbers of parentT of the given childT statement.
     * @param stmt
     * @return unordered_set<int>: The set of statement number of all s1 in ParentT(s1, stmt)
     */
    std::unordered_set<int> getParentT(int child);

    /**
     * @brief Gets the set of statement number of the children of the given parentT statement.
     * @param stmt: stmt in ParentT(stmt, s2)
     * @return unordered_set<int>: The set of statement numbers of all s2 in ParentT(stmt, s2)
     */
    std::unordered_set<int> getChildT(int parentT);

    /**
     * @brief Checks if a specific "ParentT" relationship exists between a parentT and a childT.
     * @param parentT The parentT part of the relationship to check.
     * @param childT The childT part of the relationship to check.
     * @return true if the relationship exists, false otherwise.
     */
    bool hasParentT(int parentT, int childT);

    // Inherited methods
    bool isEmpty() override;

    std::unordered_map<int, std::unordered_set<int>> getKeyValueRelationships() override;

    std::unordered_map<int, std::unordered_set<int>> getValueKeyRelationships() override;

    std::unordered_set<int> getKeys() override;

    std::unordered_set<int> getValues() override;

    std::unordered_set<int> getRelationshipsByValue(int stmtNum) override;

    std::unordered_set<int> getRelationshipsByKey(int stmtNum) override;

    bool hasRelationship(int stmt1, int stmt2) override;

    int getSize() override;

    int getRelationshipCountByKey(int stmtNum) override;

    int getRelationshipCountByValue(int stmtNum) override;
};
// ai-gen end
