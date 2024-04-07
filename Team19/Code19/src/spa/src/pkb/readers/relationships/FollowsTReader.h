#pragma once

#include <memory>

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/FollowsTStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class FollowsTReader: public IRelationshipReader<int, int> {
private:
    std::shared_ptr<FollowsTStore> followsTStore;
public:
    FollowsTReader(std::shared_ptr<FollowsTStore> store);

    // Custom methods
    /**
     * @brief Gets the preceding statement numbers of all "FollowsT" relationships.
     * @return unordered_set<int>: The set of statement numbers of s1 in FollowsT(s1, s2)
     */
    std::unordered_set<int> getAllPreFollowsT();

    /**
     * @brief Gets the post statement numbers of all "FollowsT" relationships.
     * @return unordered_set<int>: The set of statement numbers of s2 in FollowsT(s1, s2)
     */
    std::unordered_set<int> getAllPostFollowsT();

    /**
     * @brief Gets the set of statements number of reversed "FollowsT" relationships of the given statement.
     * @param stmt
     * @return unordered_set<int>: The set of statement number of all s1 in FollowsT(s1, stmt)
     */
    std::unordered_set<int> getPreFollowsT(int stmt);

    /**
     * @brief Gets the set of statements number of "FollowsT" relationships of the given statement.
     * @param stmt: stmt in FollowsT(stmt, s2)
     * @return unordered_set<int>: The set of statement numbers of all s2 in FollowsT(stmt, s2)
     */
    std::unordered_set<int> getPostFollowsT(int stmt);

    /**
     * @brief Checks if a specific "FollowsT" relationship exists between two statements.
     * @param stmt1: The statement number of the first statement.
     * @param stmt2: The statement number of the second statement.
     * @return true if the "FollowsT" relationship exists, false otherwise.
     */
    bool hasFollowsT(int stmt1, int stmt2);
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
