#pragma once

#include <memory>

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/NextTStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class NextTReader: public IRelationshipReader<int, int> {
private:
	std::shared_ptr<NextTStore> nextTStore;
public:
	NextTReader(std::shared_ptr<NextTStore> nextTStore);

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

	// Custom methods
	/**
	 * @brief Gets the preceding statement numbers of all "Next" relationships.
	 * @return unordered_set<int>: The set of statement numbers of s1 in Next(s1, s2)
	 */
	std::unordered_set<int> getAllPreviousT();

	/**
	 * @brief Gets the post statement numbers of all "Next" relationships.
	 * @return unordered_set<int>: The set of statement numbers of s2 in Next(s1, s2)
	 */
	std::unordered_set<int> getAllNextT();

	/**
	 * @brief Gets the statement number of reversed "Next" relationships of the given statement.
	 * @param stmt
	 * @return unordered_set<int>: The set of statement number of all s1 in Next(s1, stmt)
	 */
	std::unordered_set<int> getPreviousT(int stmt);

	/**
	 * @brief Gets the statement number of "Next" relationships of the given statement.
	 * @param stmt: stmt in Next(stmt, s2)
	 * @return unordered_set<int>: The set of statement numbers of all s2 in Next(stmt, s2)
	 */
	std::unordered_set<int> getNextT(int stmt);

	/**
	 * @brief Gets all "NextT" relationships.
	 * @return unordered_map<int, unordered_set<int>>: The map of all NextT relationships.
	 */
	std::unordered_map<int, std::unordered_set<int>> getAllNextTRelationships();

	/**
	 * @brief Gets all "NextT" relationships.
	 * @return unordered_map<int, unordered_set<int>>: The map of all NextT relationships.
	 */
	std::unordered_map<int, std::unordered_set<int>> getAllReversedNextTRelationships();

	/**
	 * @brief Checks if a specific "Next" relationship exists between a given statement and another statement.
	 * @param stmt1 The statement number of the first statement.
	 * @param stmt2 The statement number of the second statement.
	 * @return true if the "Next" relationship exists, false otherwise.
	 */
	bool hasNextT(int stmt1, int stmt2);
};
// ai-gen end
