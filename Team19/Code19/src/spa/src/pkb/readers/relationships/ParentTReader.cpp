#include "ParentTReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
ParentTReader::ParentTReader(std::shared_ptr<ParentTStore> store) : parentTStore(std::move(store)) {}

// Custom methods
std::unordered_set<int> ParentTReader::getAllParentTs() {
  return parentTStore->getKeys();
}

std::unordered_set<int> ParentTReader::getAllChildrenT() {
  return parentTStore->getValues();
}

std::unordered_set<int> ParentTReader::getParentT(int child) {
  return parentTStore->getRelationshipsByValue(child);
}

std::unordered_set<int> ParentTReader::getChildT(int parentT) {
  return parentTStore->getRelationshipsByKey(parentT);
}

bool ParentTReader::hasParentT(int parentT, int childT) {
  return parentTStore->hasRelationship(parentT, childT);
}

// Inherited methods
bool ParentTReader::isEmpty() {
  return parentTStore->isEmpty();
}

std::unordered_map<int, std::unordered_set<int>> ParentTReader::getKeyValueRelationships() {
  return parentTStore->getKeyValueRelationships();
}

std::unordered_map<int, std::unordered_set<int>> ParentTReader::getValueKeyRelationships() {
  return parentTStore->getValueKeyRelationships();
}

std::unordered_set<int> ParentTReader::getKeys() {
  return getAllParentTs();
}

std::unordered_set<int> ParentTReader::getValues() {
  return getAllChildrenT();
}

std::unordered_set<int> ParentTReader::getRelationshipsByValue(int stmtNum) {
  return getParentT(stmtNum);
}

std::unordered_set<int> ParentTReader::getRelationshipsByKey(int stmtNum) {
  return getChildT(stmtNum);
}

bool ParentTReader::hasRelationship(int stmt1, int stmt2) {
  return hasParentT(stmt1, stmt2);
}

int ParentTReader::getSize() {
  return parentTStore->getSize();
}

int ParentTReader::getRelationshipCountByKey(int stmtNum) {
  return parentTStore->getRelationshipCountByKey(stmtNum);
}

int ParentTReader::getRelationshipCountByValue(int stmtNum) {
  return parentTStore->getRelationshipCountByValue(stmtNum);
}
// ai-gen end
