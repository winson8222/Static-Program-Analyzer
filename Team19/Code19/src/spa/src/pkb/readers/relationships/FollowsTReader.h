#pragma once

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/FollowsTStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class FollowsTReader: public IRelationshipReader<int, int> {
private:
    std::shared_ptr<FollowsTStore> followsTStore;
public:
    explicit FollowsTReader(std::shared_ptr<FollowsTStore> store) {
      followsTStore = std::move(store);
    }

    // Inherited methods
    bool isEmpty() override {
      return followsTStore->isEmpty();
    }

    std::unordered_map<int, std::unordered_set<int>> getKeyValueRelationships() override {
      return followsTStore->getKeyValueRelationships();
    }

    std::unordered_map<int, std::unordered_set<int>> getValueKeyRelationships() override {
      return followsTStore->getValueKeyRelationships();
    }

    std::unordered_set<int> getKeys() override {
      return getAllPreFollowsT();
    }

    std::unordered_set<int> getValues() override {
      return getAllPostFollowsT();
    }

    std::unordered_set<int> getRelationshipsByValue(int stmtNum) override {
      return getPreFollowsT(stmtNum);
    }

    std::unordered_set<int> getRelationshipsByKey(int stmtNum) override {
      return getPostFollowsT(stmtNum);
    }

    bool hasRelationship(int stmt1, int stmt2) override {
      return hasFollowsT(stmt1, stmt2);
    }

    // Custom methods
    /**
     * @brief Gets the preceding statement numbers of all "FollowsT" relationships.
     * @return unordered_set<int>: The set of statement numbers of s1 in FollowsT(s1, s2)
     */
    std::unordered_set<int> getAllPreFollowsT() {
      return followsTStore->getKeys();
    }

    /**
     * @brief Gets the post statement numbers of all "FollowsT" relationships.
     * @return unordered_set<int>: The set of statement numbers of s2 in FollowsT(s1, s2)
     */
    std::unordered_set<int> getAllPostFollowsT() {
      return followsTStore->getValues();
    }

    /**
     * @brief Gets the set of statements number of reversed "FollowsT" relationships of the given statement.
     * @param stmt
     * @return unordered_set<int>: The set of statement number of all s1 in FollowsT(s1, stmt)
     */
    std::unordered_set<int> getPreFollowsT(int stmt) {
      return followsTStore->getRelationshipsByValue(stmt);
    }

    /**
     * @brief Gets the set of statements number of "FollowsT" relationships of the given statement.
     * @param stmt: stmt in FollowsT(stmt, s2)
     * @return unordered_set<int>: The set of statement numbers of all s2 in FollowsT(stmt, s2)
     */
    std::unordered_set<int> getPostFollowsT(int stmt) {
      return followsTStore->getRelationshipsByKey(stmt);
    }

    /**
     * @brief Checks if a specific "FollowsT" relationship exists between two statements.
     * @param stmt1: The statement number of the first statement.
     * @param stmt2: The statement number of the second statement.
     * @return true if the "FollowsT" relationship exists, false otherwise.
     */
    bool hasFollowsT(int stmt1, int stmt2) {
      return followsTStore->hasRelationship(stmt1, stmt2);
    }
};
// ai-gen end
