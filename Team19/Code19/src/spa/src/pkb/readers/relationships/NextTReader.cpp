#include "NextTReader.h"
#include <iostream>
// ai-gen start(copilot, 2, e)
// prompt: used copilot
NextTReader::NextTReader(std::shared_ptr<NextStore> nextStore, std::shared_ptr<NextTStore> nextTStore) :
	nextTStore(std::move(nextTStore)), nextStore(std::move(nextStore)) {}

// Inherited methods
bool NextTReader::isEmpty() {
	// Since NextStore is a subset of NextTStore, checking if NextStore is empty is sufficient
	return nextStore->isEmpty();
}

std::unordered_map<int, std::unordered_set<int>> NextTReader::getKeyValueRelationships() {
	return getAllNextTRelationships();
}

std::unordered_map<int, std::unordered_set<int>> NextTReader::getValueKeyRelationships() {
	return getAllReversedNextTRelationships();
}

std::unordered_set<int> NextTReader::getKeys() {
	return getAllPreviousT();
}

std::unordered_set<int> NextTReader::getValues() {
	return getAllNextT();
}

std::unordered_set<int> NextTReader::getRelationshipsByValue(int stmtNum) {
	return getPreviousT(stmtNum);
}

std::unordered_set<int> NextTReader::getRelationshipsByKey(int stmtNum) {
	return getNextT(stmtNum);
}

bool NextTReader::hasRelationship(int stmt1, int stmt2) {
	return hasNextT(stmt1, stmt2);
}

std::unordered_set<int> NextTReader::getAllPreviousT() {
	// Since NextStore is a subset of NextTStore, getting all previous of NextStore is sufficient
	return nextTStore->populateAndGetAllPreviousT(nextStore);
}

std::unordered_set<int> NextTReader::getAllNextT() {
	// Since NextStore is a subset of NextTStore, getting all next of NextStore is sufficient
	return nextTStore->populateAndGetAllNextT(nextStore);
}

std::unordered_set<int> NextTReader::getPreviousT(int stmt) {
	if (nextTStore->hasPreviousTPopulated(stmt)) {
		// NextTStore populated for previousT
		return nextTStore->getRelationshipsByValue(stmt);
	} else {
		// NextTStore not populated for previousT
		std::unordered_set<int> result = nextTStore->populateAndGetPreviousT(stmt, nextStore, {});
		nextTStore->populatePreviousT(stmt);
		return result;
	}
}

std::unordered_set<int> NextTReader::getNextT(int stmt) {
	if (nextTStore->hasNextTPopulated(stmt)) {
		// NextTStore populated for nextT
		return nextTStore->getRelationshipsByKey(stmt);
	} else {
		// NextTStore not populated for nextT
		std::unordered_set<int> result = nextTStore->populateAndGetNextT(stmt, nextStore, {});
		nextTStore->populateNextT(stmt);
		return result;
	}
}

std::unordered_map<int, std::unordered_set<int>> NextTReader::getAllNextTRelationships() {
	return nextTStore->populateAndGetEntireNextTStore(nextStore, false);
}

std::unordered_map<int, std::unordered_set<int>> NextTReader::getAllReversedNextTRelationships() {
	return nextTStore->populateAndGetEntireNextTStore(nextStore, true);
}

bool NextTReader::hasNextT(int stmt1, int stmt2) {
	if (nextTStore->hasNextTPopulated(stmt1)) {
		// NextTStore populated for nextT
		return nextTStore->hasRelationship(stmt1, stmt2);
	} else {
		// NextTStore not populated for nextT
		std::unordered_set<int> nextTSet = nextTStore->populateAndGetNextT(stmt1, nextStore, {});
		return nextTSet.find(stmt2) != nextTSet.end();
	}
}
// ai-gen end
