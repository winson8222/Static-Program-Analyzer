#pragma once

#include <memory>

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/AffectsStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class AffectsReader: public IRelationshipReader<int, int> {
private:
    std::shared_ptr<AffectsStore> affectsStore;
public:
    AffectsReader(std::shared_ptr<AffectsStore> store);

    // Inherited methods
    bool isEmpty() override;
    std::unordered_map<int, std::unordered_set<int>> getKeyValueRelationships() override;
    std::unordered_map<int, std::unordered_set<int>> getValueKeyRelationships() override;
    std::unordered_set<int> getKeys() override;
    std::unordered_set<int> getValues() override;
    std::unordered_set<int> getRelationshipsByValue(int stmtNum) override;
    std::unordered_set<int> getRelationshipsByKey(int stmtNum) override;
    bool hasRelationship(int stmt1, int stmt2) override;

    // Custom methods
    /**
     * @brief Gets the affecting statement numbers of all "Affects" relationships.
     * @return unordered_set<int>: The set of statement numbers of s1 in Affects(s1, s2)
     */
     std::unordered_set<int> getAllAffecting();

     /**
     * @brief Gets the affected statement numbers of all "Affects" relationships.
     * @return unordered_set<int>: The set of statement numbers of s2 in Affects(s1, s2)
     */
     std::unordered_set<int> getAllAffected();

     /**
     * @brief Gets the set of statement numbers that affect the given statement.
     * @param stmt
     * @return unordered_set<int>: The set of statement number of all s1 in Affects(s1, stmt)
     */
     std::unordered_set<int> getAffecting(int stmt);

     /**
     * @brief Gets the set of statement numbers that the given statement affects.
     * @param stmt: stmt in Affects(stmt, s2)
     * @return unordered_set<int>: The set of statement numbers of all s2 in Affects(stmt, s2)
     */
     std::unordered_set<int> getAffected(int stmt);

     /**
     * @brief Checks if a specific "Affects" relationship exists between a given statement and another statement.
     * @param stmt1 The statement number of the affecting statement.
     * @param stmt2 The statement number of the affected statement.
     * @return true if the "Affects" relationship exists, false otherwise.
     */
     bool hasAffects(int stmt1, int stmt2);
};
// ai-gen end
