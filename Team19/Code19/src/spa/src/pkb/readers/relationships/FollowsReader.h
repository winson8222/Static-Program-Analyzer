#pragma once

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/FollowsStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class FollowsReader: public IRelationshipReader<int, int> {
private:
    std::shared_ptr<FollowsStore> followsStore;
public:
    explicit FollowsReader(std::shared_ptr<FollowsStore> store) {
      followsStore = std::move(store);
    }

    // Inherited methods
    bool isEmpty() override {
      return followsStore->isEmpty();
    }

    std::unordered_map<int, std::unordered_set<int>> getKeyValueRelationships() override {
      return followsStore->getKeyValueRelationships();
    }

    std::unordered_map<int, std::unordered_set<int>> getValueKeyRelationships() override {
      return followsStore->getValueKeyRelationships();
    }

    std::unordered_set<int> getKeys() override {
      return getAllPreFollows();
    }

    std::unordered_set<int> getValues() override {
      return getAllPostFollows();
    }

    std::unordered_set<int> getRelationshipsByValue(int stmtNum) override {
      return getPreFollows(stmtNum);
    }

    std::unordered_set<int> getRelationshipsByKey(int stmtNum) override {
      return getPostFollows(stmtNum);
    }

    bool hasRelationship(int stmt1, int stmt2) override {
      return hasFollows(stmt1, stmt2);
    }

    // Custom methods
    /**
     * @brief Gets the preceding statement numbers of all "Follows" relationships.
     * @return unordered_set<int>: The set of statement numbers of s1 in Follows(s1, s2)
     */
    std::unordered_set<int> getAllPreFollows() {
      return followsStore->getKeys();
    }

    /**
     * @brief Gets the post statement numbers of all "Follows" relationships.
     * @return unordered_set<int>: The set of statement numbers of s2 in Follows(s1, s2)
     */
    std::unordered_set<int> getAllPostFollows() {
      return followsStore->getValues();
    }

    /**
     * @brief Gets the statement number of reversed "Follows" relationships of the given statement.
     * @param stmt
     * @return unordered_set<int>: The set of statement number of all s1 in Follows(s1, stmt)
     */
    std::unordered_set<int> getPreFollows(int stmt) {
      return followsStore->getRelationshipsByValue(stmt);
    }

    /**
     * @brief Gets the statement number of "Follows" relationships of the given statement.
     * @param stmt: stmt in Follows(stmt, s2)
     * @return unordered_set<int>: The set of statement numbers of all s2 in Follows(stmt, s2)
     */
    std::unordered_set<int> getPostFollows(int stmt) {
      return followsStore->getRelationshipsByKey(stmt);
    }

    /**
     * @brief Checks if a specific "Follows" relationship exists between a given statement and another statement.
     * @param stmt1 The statement number of the first statement.
     * @param stmt2 The statement number of the second statement.
     * @return true if the "Follows" relationship exists, false otherwise.
     */
    bool hasFollows(int stmt1, int stmt2) {
      return followsStore->hasRelationship(stmt1, stmt2);
    }
};
// ai-gen end
