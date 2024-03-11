#include "FollowsTReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
FollowsTReader::FollowsTReader(std::shared_ptr<FollowsTStore> store) : followsTStore(std::move(store)) {}


// Inherited methods
bool FollowsTReader::isEmpty() {
  return followsTStore->isEmpty();
}

std::unordered_map<int, std::unordered_set<int>> FollowsTReader::getKeyValueRelationships() {
  return followsTStore->getKeyValueRelationships();
}

std::unordered_map<int, std::unordered_set<int>> FollowsTReader::getValueKeyRelationships() {
  return followsTStore->getValueKeyRelationships();
}

std::unordered_set<int> FollowsTReader::getKeys() {
  return getAllPreFollowsT();
}

std::unordered_set<int> FollowsTReader::getValues() {
  return getAllPostFollowsT();
}

std::unordered_set<int> FollowsTReader::getRelationshipsByValue(int stmtNum) {
  return getPreFollowsT(stmtNum);
}

std::unordered_set<int> FollowsTReader::getRelationshipsByKey(int stmtNum) {
  return getPostFollowsT(stmtNum);
}

bool FollowsTReader::hasRelationship(int stmt1, int stmt2) {
  return hasFollowsT(stmt1, stmt2);
}

std::unordered_set<int> FollowsTReader::getAllPreFollowsT() {
  return followsTStore->getKeys();
}

std::unordered_set<int> FollowsTReader::getAllPostFollowsT() {
  return followsTStore->getValues();
}

std::unordered_set<int> FollowsTReader::getPreFollowsT(int stmt) {
  return followsTStore->getRelationshipsByValue(stmt);
}

std::unordered_set<int> FollowsTReader::getPostFollowsT(int stmt) {
  return followsTStore->getRelationshipsByKey(stmt);
}

bool FollowsTReader::hasFollowsT(int stmt1, int stmt2) {
  return followsTStore->hasRelationship(stmt1, stmt2);
}
// ai-gen end
