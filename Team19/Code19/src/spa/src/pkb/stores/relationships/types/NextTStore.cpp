#include "NextTStore.h"
#include <iostream>
// ai-gen start(copilot, 2, e)
// prompt: used copilot

NextTStore::NextTStore(std::shared_ptr<NextStore> nextStore, std::shared_ptr<WhileStore> whileStore, std::shared_ptr<ParentTStore> parentTStore) :nextStore(std::move(nextStore)), whileStore(std::move(whileStore)), parentTStore(std::move(parentTStore)) {}

std::unordered_set<int> NextTStore::populateAndGetPreviousT(int stmt, std::unordered_set<int> visited) {
	if (hasPreviousTPopulated(stmt)) {
		return NextTStore::getRelationshipsByValue(stmt);
	}
	if (whileStore->contains(stmt)) {
		addRelationship(stmt, stmt);
	}
	std::unordered_set<int> result;
	std::unordered_set<int> previousSet = nextStore->getRelationshipsByValue(stmt);
	visited.insert(stmt);
	for (int previous : previousSet) {
		NextTStore::addRelationship(previous, stmt);
		result.insert(previous);
		if (visited.find(previous) != visited.end()) continue;
		std::unordered_set<int> previousPreviousSet = NextTStore::populateAndGetPreviousT(previous, visited);
		addRelationshipAndResult(stmt, result, previousPreviousSet, true);
	}
	return result;
};

std::unordered_set<int> NextTStore::populateAndGetNextT(int stmt, std::unordered_set<int> visited) {
	if (hasNextTPopulated(stmt)) {
		return NextTStore::getRelationshipsByKey(stmt);
	}

	std::unordered_set<int> result;
	if (whileStore->contains(stmt)) {
		addRelationship(stmt, stmt);
		result.insert(stmt);
	}
	std::unordered_set<int> nextSet = nextStore->getRelationshipsByKey(stmt);
	visited.insert(stmt);
	for (int next : nextSet) {
		NextTStore::addRelationship(stmt, next);
		result.insert(next);
		if (visited.find(next) != visited.end()) continue;
		std::unordered_set<int> nextNextSet = NextTStore::populateAndGetNextT(next, visited);
		addRelationshipAndResult(stmt, result, nextNextSet, false);
	}
	return result;
};

std::unordered_map<int, std::unordered_set<int>> NextTStore::populateAndGetEntireNextTStore(bool reversed) {
	std::unordered_set<int> previousSet = populateAndGetAllPreviousT();
	std::unordered_set<int> nextSet = populateAndGetAllNextT();
	std::unordered_map<int, std::unordered_set<int>> result;
	for (int i : reversed ? nextSet : previousSet) {
		result[i] = reversed ? NextTStore::getRelationshipsByValue(i) : NextTStore::getRelationshipsByKey(i);
	}
	return result;
}

std::unordered_set<int> NextTStore::populateAndGetAllPreviousT() {
	std::unordered_set<int> result;
	for (int i : nextStore->getValues()) {
		if (NextTStore::hasPreviousTPopulated(i)) {
			for (int j : NextTStore::getRelationshipsByValue(i)) {
				result.insert(j);
			}
			continue;
		}
		std::unordered_set<int> previousTSet = NextTStore::populateAndGetPreviousT(i, std::unordered_set<int>{});
		for (int j : previousTSet) {
			result.insert(j);
		}
		NextTStore::logPreviousTAdded(i);
	}
	return result;
}

std::unordered_set<int> NextTStore::populateAndGetAllNextT() {
	std::unordered_set<int> result;
	for (int i : nextStore->getKeys()) {
		if (NextTStore::hasNextTPopulated(i)) {
			for (int j : NextTStore::getRelationshipsByKey(i)) {
				result.insert(j);
			}
			continue;
		}
		std::unordered_set<int> nextTSet = NextTStore::populateAndGetNextT(i, std::unordered_set<int>{});

		for (int j : nextTSet) {
			result.insert(j);
		}
		NextTStore::logNextTAdded(i);
	}
	return result;
}

void NextTStore::populateAllNextT() {
    for (int i : nextStore->getKeys()) {
        if (NextTStore::hasNextTPopulated(i)) continue;
		if (whileStore->contains(i)) {
			addRelationship(i, i);
			std::unordered_set<int> whileChildren = parentTStore->getRelationshipsByKey(i);
			for (int child : whileChildren) {
				addRelationship(child, child);
			}
		}
        NextTStore::populateNextT(i, {});
        NextTStore::logNextTAdded(i);
    }
}

void NextTStore::populateNextT(int stmt, std::unordered_set<int> visited) {
    if (hasNextTPopulated(stmt)) return;
    std::unordered_set<int> nextSet = nextStore->getRelationshipsByKey(stmt);
    visited.insert(stmt);
    for (int next : nextSet) {
        NextTStore::addRelationship(stmt, next);
        if (visited.find(next) != visited.end()) continue;
        std::unordered_set<int> nextNextSet = NextTStore::populateAndGetNextT(next, visited);
        addRelationshipOnly(stmt, nextNextSet, false);
    }
}

void NextTStore::populateAllPreviousT() {
    for (int i : nextStore->getValues()) {
        if (NextTStore::hasPreviousTPopulated(i)) continue;
        NextTStore::populatePreviousT(i, {});
        NextTStore::logPreviousTAdded(i);
    }
}

void NextTStore::populatePreviousT(int stmt, std::unordered_set<int> visited) {
    if (hasPreviousTPopulated(stmt)) return;
    std::unordered_set<int> previousSet = nextStore->getRelationshipsByValue(stmt);
    visited.insert(stmt);
    for (int previous: previousSet) {
        NextTStore::addRelationship(previous, stmt);
        if (visited.find(previous) != visited.end()) continue;
        std::unordered_set<int> previousPreviousSet = NextTStore::populateAndGetPreviousT(previous, visited);
        addRelationshipOnly(stmt, previousPreviousSet, true);
    }
}

void NextTStore::addRelationshipAndResult(int stmt, std::unordered_set<int>& result, const std::unordered_set<int>& set, bool reversed) {
	for (int i : set) {
		if (i == stmt) continue;
		result.insert(i);
		reversed ? NextTStore::addRelationship(i, stmt) : NextTStore::addRelationship(stmt, i);
	}
}

void NextTStore::addRelationshipOnly(int stmt, const std::unordered_set<int>& set, bool reversed) {
    for (int i : set) {
        if (i == stmt) continue;
        reversed ? NextTStore::addRelationship(i, stmt) : NextTStore::addRelationship(stmt, i);
    }
}

void NextTStore::logNextTAdded(int stmt) {
	nextTPopulated.insert(stmt);
}

void NextTStore::logPreviousTAdded(int stmt) {
	previousTPopulated.insert(stmt);
}

bool NextTStore::hasPreviousTPopulated(int stmt) {
	return previousTPopulated.find(stmt) != previousTPopulated.end();
}

bool NextTStore::hasNextTPopulated(int stmt) {
	return nextTPopulated.find(stmt) != nextTPopulated.end();
}

bool NextTStore::populateNextTStore() {
	populateAllNextT();
	populateAllPreviousT();
	return true;
}

std::unordered_set<int> NextTStore::getNextT(int stmt) {
	return NextTStore::getRelationshipsByKey(stmt);
}

std::unordered_set<int> NextTStore::getPreviousT(int stmt) {
	return NextTStore::getRelationshipsByValue(stmt);
}

std::unordered_set<int> NextTStore::getAllPreviousT() {
	return NextTStore::getKeys();
}

std::unordered_set<int> NextTStore::getAllNextT() {
	return NextTStore::getValues();
}

void NextTStore::clear() {
	RelationshipStore<int, int>::clear();
	nextTPopulated.clear();
	previousTPopulated.clear();
}
// ai-gen end
