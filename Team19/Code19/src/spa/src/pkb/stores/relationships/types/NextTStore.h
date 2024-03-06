#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <memory>

#include "pkb/stores/relationships/RelationshipStore.h"
#include "pkb/stores/relationships/types/NextStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @class NextTStore
 * Manages "Next" relationships for statements in a SIMPLE program.
 * This store captures relationships where a particular statement (identified by number)
 * modifies a certain variable.
 *
 * Inherits from RelationshipStore<int, int> to provide functionality for managing
 * relationships between statements and the statements that they are next to.
 *
 * Due to the constraints of the project, this class is used only as a cache for the NextT relationships.
 * It is only populated during the NextT query and is cleared after the query is completed.
 */
class NextTStore : public RelationshipStore<int, int> {
private:
	std::unordered_set<int> nextTPopulated;
	std::unordered_set<int> previousTPopulated;
	void addRelationshipAndResult(int stmt, std::unordered_set<int>& result, const std::unordered_set<int>& set, bool reversed);
public:
	bool hasNextTPopulated(int stmt);
	bool hasPreviousTPopulated(int stmt);
	void populateNextT(int stmt);
	void populatePreviousT(int stmt);

	std::unordered_map<int, std::unordered_set<int>> populateAndGetEntireNextTStore(const std::shared_ptr<NextStore>& nextStore, bool reversed);

	// Populate and get
	std::unordered_set<int> populateAndGetNextT(int stmt, const std::shared_ptr<NextStore>& nextStore, std::unordered_set<int> visited);
	std::unordered_set<int> populateAndGetPreviousT(int stmt, const std::shared_ptr<NextStore>& nextStore, std::unordered_set<int> visited);

	std::unordered_set<int> populateAndGetAllPreviousT(const std::shared_ptr<NextStore>& nextStore);
	std::unordered_set<int> populateAndGetAllNextT(const std::shared_ptr<NextStore>& nextStore);

	// Get only
	std::unordered_set<int> getNextT(int stmt);
	std::unordered_set<int> getPreviousT(int stmt);
	std::unordered_set<int> getAllPreviousT();
	std::unordered_set<int> getAllNextT();

	bool populateNextTStore(const std::shared_ptr<NextStore>& nextStore);

	void clear() override;
};
// ai-gen end
