#include "FollowsReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
FollowsReader::FollowsReader(std::shared_ptr<FollowsStore> store) : followsStore(std::move(store)) {}

// Inherited methods
bool FollowsReader::isEmpty() {
  return followsStore->isEmpty();
}

std::unordered_map<int, std::unordered_set<int>> FollowsReader::getKeyValueRelationships() {
  return followsStore->getKeyValueRelationships();
}

std::unordered_map<int, std::unordered_set<int>> FollowsReader::getValueKeyRelationships() {
  return followsStore->getValueKeyRelationships();
}

std::unordered_set<int> FollowsReader::getKeys() {
  return getAllPreFollows();
}

std::unordered_set<int> FollowsReader::getValues() {
  return getAllPostFollows();
}

std::unordered_set<int> FollowsReader::getRelationshipsByValue(int stmtNum) {
  return getPreFollows(stmtNum);
}

std::unordered_set<int> FollowsReader::getRelationshipsByKey(int stmtNum) {
  return getPostFollows(stmtNum);
}

int FollowsReader::getSize() {
  return followsStore->getSize();
}

int FollowsReader::getRelationshipCountByKey(int stmtNum) {
  return followsStore->getRelationshipCountByKey(stmtNum);
}

int FollowsReader::getRelationshipCountByValue(int stmtNum) {
  return followsStore->getRelationshipCountByValue(stmtNum);
}

bool FollowsReader::hasRelationship(int stmt1, int stmt2) {
  return hasFollows(stmt1, stmt2);
}

std::unordered_set<int> FollowsReader::getAllPreFollows() {
  return followsStore->getKeys();
}

std::unordered_set<int> FollowsReader::getAllPostFollows() {
  return followsStore->getValues();
}

std::unordered_set<int> FollowsReader::getPreFollows(int stmt) {
  return followsStore->getRelationshipsByValue(stmt);
}

std::unordered_set<int> FollowsReader::getPostFollows(int stmt) {
  return followsStore->getRelationshipsByKey(stmt);
}

bool FollowsReader::hasFollows(int stmt1, int stmt2) {
  return followsStore->hasRelationship(stmt1, stmt2);
}
// ai-gen end
