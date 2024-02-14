#pragma once

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/ParentTStore.h"

class ParentTReader: public IRelationshipReader<int, int> {
private:
    std::shared_ptr<ParentTStore> parentTStore;
public:
    explicit ParentTReader(std::shared_ptr<ParentTStore> store) {
      parentTStore = std::move(store);
    }

    // Inherited methods
    bool isEmpty() override {
      return parentTStore->isEmpty();
    }

    std::unordered_map<int, std::unordered_set<int>> getKeyValueRelationships() override {
      return parentTStore->getKeyValueRelationships();
    }

    std::unordered_map<int, std::unordered_set<int>> getValueKeyRelationships() override {
      return parentTStore->getValueKeyRelationships();
    }

    std::unordered_set<int> getKeys() override {
      return getAllParentTs();
    }

    std::unordered_set<int> getValues() override {
      return getAllChildrenT();
    }

    std::unordered_set<int> getRelationshipsByValue(int stmtNum) override {
      return getParentT(stmtNum);
    }

    std::unordered_set<int> getRelationshipsByKey(int stmtNum) override {
      return getChildT(stmtNum);
    }

    bool hasRelationship(int stmt1, int stmt2) override {
      return hasParentT(stmt1, stmt2);
    }

    // Custom methods
    /**
     * @brief Gets the parentT statement numbers of all "ParentT" relationships.
     * @return unordered_set<int>: The set of statement numbers of s1 in ParentT(s1, s2)
     */
    std::unordered_set<int> getAllParentTs() {
      return parentTStore->getKeys();
    }

    /**
     * @brief Gets the childT statement numbers of all "ParentT" relationships.
     * @return unordered_set<int>: The set of statement numbers of s2 in ParentT(s1, s2)
     */
    std::unordered_set<int> getAllChildrenT() {
      return parentTStore->getValues();
    }

    /**
     * @brief Gets the set of statement numbers of parentT of the given childT statement.
     * @param stmt
     * @return unordered_set<int>: The set of statement number of all s1 in ParentT(s1, stmt)
     */
    std::unordered_set<int> getParentT(int child) {
      return parentTStore->getRelationshipsByValue(child);
    }

    /**
     * @brief Gets the set of statement number of the children of the given parentT statement.
     * @param stmt: stmt in ParentT(stmt, s2)
     * @return unordered_set<int>: The set of statement numbers of all s2 in ParentT(stmt, s2)
     */
    std::unordered_set<int> getChildT(int parentT) {
      return parentTStore->getRelationshipsByKey(parentT);
    }

    /**
     * @brief Checks if a specific "ParentT" relationship exists between a parentT and a childT.
     * @param parentT The parentT part of the relationship to check.
     * @param childT The childT part of the relationship to check.
     * @return true if the relationship exists, false otherwise.
     */
    bool hasParentT(int parentT, int childT) {
      return parentTStore->hasRelationship(parentT, childT);
    }

};
