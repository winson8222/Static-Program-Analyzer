#include "NextTReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
NextTReader::NextTReader(std::shared_ptr<NextTStore> nextTStore) : nextTStore(std::move(nextTStore)) {}

// Inherited methods
bool NextTReader::isEmpty() {
	return nextTStore->isEmpty();
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
	return nextTStore->populateAndGetAllPreviousT();
}

std::unordered_set<int> NextTReader::getAllNextT() {
	return nextTStore->populateAndGetAllNextT();
}

std::unordered_set<int> NextTReader::getPreviousT(int stmt) {
	if (nextTStore->hasPreviousTPopulated(stmt)) {
		// NextTStore populated for previousT
		return nextTStore->getRelationshipsByValue(stmt);
	} else {
		// NextTStore not populated for previousT
		std::unordered_set<int> result = nextTStore->populateAndGetPreviousT(stmt, {});
		nextTStore->logPreviousTAdded(stmt);
		return result;
	}
}

std::unordered_set<int> NextTReader::getNextT(int stmt) {
	if (nextTStore->hasNextTPopulated(stmt)) {
		// NextTStore populated for nextT
		return nextTStore->getRelationshipsByKey(stmt);
	} else {
		// NextTStore not populated for nextT
		std::unordered_set<int> result = nextTStore->populateAndGetNextT(stmt, {});
		nextTStore->logNextTAdded(stmt);
		return result;
	}
}

std::unordered_map<int, std::unordered_set<int>> NextTReader::getAllNextTRelationships() {
	return nextTStore->getKeyValueRelationships();
}

std::unordered_map<int, std::unordered_set<int>> NextTReader::getAllReversedNextTRelationships() {
	return nextTStore->getValueKeyRelationships();
}

bool NextTReader::hasNextT(int stmt1, int stmt2) {
	return nextTStore->hasRelationship(stmt1, stmt2);
}
// ai-gen end
