#include "NextReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
NextReader::NextReader(std::shared_ptr<NextStore> store) : nextStore(std::move(store)) {}

// Inherited methods
bool NextReader::isEmpty() {
	return nextStore->isEmpty();
}

std::unordered_map<int, std::unordered_set<int>> NextReader::getKeyValueRelationships() {
	return nextStore->getKeyValueRelationships();
}

std::unordered_map<int, std::unordered_set<int>> NextReader::getValueKeyRelationships() {
	return nextStore->getValueKeyRelationships();
}

std::unordered_set<int> NextReader::getKeys() {
	return getAllPrevious();
}

std::unordered_set<int> NextReader::getValues() {
	return getAllNext();
}

std::unordered_set<int> NextReader::getRelationshipsByValue(int stmtNum) {
	return getPrevious(stmtNum);
}

std::unordered_set<int> NextReader::getRelationshipsByKey(int stmtNum) {
	return getNext(stmtNum);
}

bool NextReader::hasRelationship(int stmt1, int stmt2) {
	return hasNext(stmt1, stmt2);
}

std::unordered_set<int> NextReader::getAllPrevious() {
	return nextStore->getKeys();
}

std::unordered_set<int> NextReader::getAllNext() {
	return nextStore->getValues();
}

std::unordered_set<int> NextReader::getPrevious(int stmt) {
	return nextStore->getRelationshipsByValue(stmt);
}

std::unordered_set<int> NextReader::getNext(int stmt) {
	return nextStore->getRelationshipsByKey(stmt);
}

bool NextReader::hasNext(int stmt1, int stmt2) {
	return nextStore->hasRelationship(stmt1, stmt2);
}
// ai-gen end
