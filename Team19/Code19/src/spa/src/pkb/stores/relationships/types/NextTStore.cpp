#include "NextTStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * Recursively populates and returns all previousT relationships for a given statement.
 * @param stmt The statement number to populate previousT relationships for.
 * @param nextStore The NextStore to get the next relationships from.
 * @param visited The set of visited statements to prevent infinite recursion.
 * @return The set of all previousT relationships for the given statement.
 */
std::unordered_set<int> NextTStore::populateAndGetPreviousT(int stmt, const std::shared_ptr<NextStore>& nextStore, std::unordered_set<int> visited) {
	if (hasPreviousTPopulated(stmt)) {
		return NextTStore::getRelationshipsByValue(stmt);
	}
	std::unordered_set<int> result;
  	std::unordered_set<int> previousSet = nextStore->getRelationshipsByValue(stmt);
	visited.insert(stmt);
	for (int previous : previousSet) {
		NextTStore::addRelationship(previous, stmt);
		result.insert(previous);
		if (visited.find(previous) != visited.end()) continue;
		std::unordered_set<int> previousPreviousSet = NextTStore::populateAndGetPreviousT(previous, nextStore, visited);
		addRelationshipAndResult(stmt, result, previousPreviousSet, true);
	}
	return result;
};

/**
 * Recursively populates and returns all nextT relationships for a given statement.
 * @param stmt The statement number to populate nextT relationships for.
 * @param nextStore The NextStore to get the next relationships from.
 * @param visited The set of visited statements to prevent infinite recursion.
 * @return The set of all nextT relationships for the given statement.
 */
std::unordered_set<int> NextTStore::populateAndGetNextT(int stmt, const std::shared_ptr<NextStore>& nextStore, std::unordered_set<int> visited) {
	if (hasNextTPopulated(stmt)) {
		return NextTStore::getRelationshipsByKey(stmt);
	}
	std::unordered_set<int> result;
	std::unordered_set<int> nextSet = nextStore->getRelationshipsByKey(stmt);
	visited.insert(stmt);
	for (int next : nextSet) {
		NextTStore::addRelationship(stmt, next);
		result.insert(next);
		if (visited.find(next) != visited.end()) continue;
		std::unordered_set<int> nextNextSet = NextTStore::populateAndGetNextT(next, nextStore, visited);
		addRelationshipAndResult(stmt, result, nextNextSet, false);
	}
	return result;
};

/**
 * Populates and returns all nextT relationships for all statements in the given NextStore.
 * @param nextStore The NextStore to get the next relationships from.
 * @param reversed Whether to get the nextT relationships in reverse.
 * @return The map of all nextT relationships for all statements in the given NextStore.
 */
std::unordered_map<int, std::unordered_set<int>> NextTStore::populateAndGetEntireNextTStore(const std::shared_ptr<NextStore>& nextStore, bool reversed) {
	std::unordered_set<int> previousSet = populateAndGetAllPreviousT(nextStore);
	std::unordered_set<int> nextSet = populateAndGetAllNextT(nextStore);
	std::unordered_map<int, std::unordered_set<int>> result;
	for (int i : reversed ? nextSet : previousSet) {
		result[i] = reversed ? NextTStore::getRelationshipsByValue(i) : NextTStore::getRelationshipsByKey(i);
	}
	return result;
}

/**
 * Populates and returns all previousT relationships for all statements in the given NextStore.
 * @param nextStore The NextStore to get the next relationships from.
 * @return The set of all previousT relationships for all statements in the given NextStore.
 */
std::unordered_set<int> NextTStore::populateAndGetAllPreviousT(const std::shared_ptr<NextStore>& nextStore) {
	std::unordered_set<int> result;
	for (int i : nextStore->getValues()) {
		if (NextTStore::hasPreviousTPopulated(i)) {
			result.insert(NextTStore::getRelationshipsByValue(i).begin(), NextTStore::getRelationshipsByValue(i).end());
			continue;
		}
		std::unordered_set<int> previousTSet = NextTStore::populateAndGetPreviousT(i, nextStore, std::unordered_set<int>{});
		result.insert(previousTSet.begin(), previousTSet.end());
		NextTStore::populatePreviousT(i);
	}
	return result;
}

/**
 * Populates and returns all nextT relationships for all statements in the given NextStore.
 * @param nextStore The NextStore to get the next relationships from.
 * @return The set of all nextT relationships for all statements in the given NextStore.
 */
std::unordered_set<int> NextTStore::populateAndGetAllNextT(const std::shared_ptr<NextStore>& nextStore) {
	std::unordered_set<int> result;
	for (int i : nextStore->getKeys()) {
		if (NextTStore::hasNextTPopulated(i)) {
			result.insert(NextTStore::getRelationshipsByKey(i).begin(), NextTStore::getRelationshipsByKey(i).end());
			continue;
		}
		std::unordered_set<int> nextTSet = NextTStore::populateAndGetNextT(i, nextStore, std::unordered_set<int>{});
		result.insert(nextTSet.begin(), nextTSet.end());
		NextTStore::populateNextT(i);
	}
	return result;
}

/**
 * Adds a relationship between two statements and adds the result to the given set.
 * @param stmt The statement number to add the relationship for.
 * @param result The set to add the result to.
 * @param set The set to add the relationship from.
 * @param reversed Whether to add the relationship in reverse.
 */
void NextTStore::addRelationshipAndResult(int stmt, std::unordered_set<int>& result, const std::unordered_set<int>& set, bool reversed) {
	for (int i : set) {
		if (i == stmt) continue;
		result.insert(i);
		reversed ? NextTStore::addRelationship(i, stmt) : NextTStore::addRelationship(stmt, i);
	}
}

/**
 * Populates the nextT relationships for a given statement.
 * @param stmt The statement number to populate nextT relationships for.
 */
void NextTStore::populateNextT(int stmt) {
	nextTPopulated.insert(stmt);
}

/**
 * Populates the previousT relationships for a given statement.
 * @param stmt The statement number to populate previousT relationships for.
 */
void NextTStore::populatePreviousT(int stmt) {
	previousTPopulated.insert(stmt);
}

/**
 * Checks if the nextT relationships for a given statement are populated.
 * @param stmt The statement number to check.
 * @return True if the nextT relationships are populated, false otherwise.
 */
bool NextTStore::hasPreviousTPopulated(int stmt) {
	return previousTPopulated.find(stmt) != previousTPopulated.end();
}

/**
 * Checks if the previousT relationships for a given statement are populated.
 * @param stmt The statement number to check.
 * @return True if the previousT relationships are populated, false otherwise.
 */
bool NextTStore::hasNextTPopulated(int stmt) {
	return nextTPopulated.find(stmt) != nextTPopulated.end();
}

/**
 * Populates the entire NextTStore with the nextT relationships from the given NextStore.
 */
bool NextTStore::populateNextTStore(const std::shared_ptr<NextStore>& nextStore) {
	populateAndGetAllNextT(nextStore);
	populateAndGetAllPreviousT(nextStore);
	return true;
}

/**
 * Gets the nextT relationships for a given statement.
 * @param stmt The statement number to get the nextT relationships for.
 * @return The set of nextT relationships for the given statement.
 */
std::unordered_set<int> NextTStore::getNextT(int stmt) {
	return NextTStore::getRelationshipsByKey(stmt);
}

/**
 * Gets the previousT relationships for a given statement.
 * @param stmt The statement number to get the previousT relationships for.
 * @return The set of previousT relationships for the given statement.
 */
std::unordered_set<int> NextTStore::getPreviousT(int stmt) {
	return NextTStore::getRelationshipsByValue(stmt);
}

/**
 * Gets all previousT relationships for all statements.
 * @return The set of all previousT relationships for all statements.
 */
std::unordered_set<int> NextTStore::getAllPreviousT() {
	return NextTStore::getKeys();
}

/**
 * Gets all nextT relationships for all statements.
 * @return The set of all nextT relationships for all statements.
 */
std::unordered_set<int> NextTStore::getAllNextT() {
	return NextTStore::getValues();
}

/**
 * Clears the store of all relationships.
 */
void NextTStore::clear() {
	RelationshipStore<int, int>::clear();
	nextTPopulated.clear();
	previousTPopulated.clear();
}
// ai-gen end
