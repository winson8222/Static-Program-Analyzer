#pragma once

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/ParentStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ParentReader: public IRelationshipReader<int, int> {
private:
    std::shared_ptr<ParentStore> parentStore;
public:
    explicit ParentReader(std::shared_ptr<ParentStore> store) {
      parentStore = std::move(store);
    }

    // Inherited methods
    bool isEmpty() override {
      return parentStore->isEmpty();
    }

    std::unordered_map<int, std::unordered_set<int>> getKeyValueRelationships() override {
      return parentStore->getKeyValueRelationships();
    }

    std::unordered_map<int, std::unordered_set<int>> getValueKeyRelationships() override {
      return parentStore->getValueKeyRelationships();
    }

    std::unordered_set<int> getKeys() override {
      return getAllParents();
    }

    std::unordered_set<int> getValues() override {
      return getAllChildren();
    }

    std::unordered_set<int> getRelationshipsByValue(int stmtNum) override {
      return getParent(stmtNum);
    }

    std::unordered_set<int> getRelationshipsByKey(int stmtNum) override {
      return getChild(stmtNum);
    }

    bool hasRelationship(int stmt1, int stmt2) override {
      return hasParent(stmt1, stmt2);
    }

    // Custom methods
    /**
     * @brief Gets the parent statement numbers of all "Parent" relationships.
     * @return unordered_set<int>: The set of statement numbers of s1 in Parent(s1, s2)
     */
    std::unordered_set<int> getAllParents() {
      return parentStore->getKeys();
    }

    /**
     * @brief Gets the child statement numbers of all "Parent" relationships.
     * @return unordered_set<int>: The set of statement numbers of s2 in Parent(s1, s2)
     */
    std::unordered_set<int> getAllChildren() {
      return parentStore->getValues();
    }

    /**
     * @brief Gets the statement number of parent of the given child statement.
     * @param stmt
     * @return unordered_set<int>: The set of statement number of all s1 in Parent*(s1, stmt)
     */
    std::unordered_set<int> getParent(int child) {
      return parentStore->getRelationshipsByValue(child);
    }

    /**
     * @brief Gets the statement number of the child of the given parent statement.
     * @param stmt: stmt in Parent(stmt, s2)
     * @return unordered_set<int>: The set of statement numbers of all s2 in Parent(stmt, s2)
     */
    std::unordered_set<int> getChild(int parent) {
      return parentStore->getRelationshipsByKey(parent);
    }

    /**
     * @brief Checks if a specific relationship exists between a parent and a child.
     * @param parent The parent part of the relationship to check.
     * @param child The child part of the relationship to check.
     * @return true if the relationship exists, false otherwise.
     */
    bool hasParent(int parent, int child) {
      return parentStore->hasRelationship(parent, child);
    }
};
// ai-gen end
