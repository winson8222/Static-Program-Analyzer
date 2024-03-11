#include "ParentReader.h"

ParentReader::ParentReader(std::shared_ptr<ParentStore> store) : parentStore(std::move(store)) {}

// Custom methods
std::unordered_set<int> ParentReader::getAllParents() {
  return parentStore->getKeys();
}

std::unordered_set<int> ParentReader::getAllChildren() {
  return parentStore->getValues();
}

std::unordered_set<int> ParentReader::getParent(int child) {
  return parentStore->getRelationshipsByValue(child);
}

std::unordered_set<int> ParentReader::getChild(int parent) {
  return parentStore->getRelationshipsByKey(parent);
}

bool ParentReader::hasParent(int parent, int child) {
  return parentStore->hasRelationship(parent, child);
}

// Inherited methods
bool ParentReader::isEmpty() {
  return parentStore->isEmpty();
}

std::unordered_map<int, std::unordered_set<int>> ParentReader::getKeyValueRelationships() {
  return parentStore->getKeyValueRelationships();
}

std::unordered_map<int, std::unordered_set<int>> ParentReader::getValueKeyRelationships() {
  return parentStore->getValueKeyRelationships();
}

std::unordered_set<int> ParentReader::getKeys() {
  return getAllParents();
}

std::unordered_set<int> ParentReader::getValues() {
  return getAllChildren();
}

std::unordered_set<int> ParentReader::getRelationshipsByValue(int stmtNum) {
  return getParent(stmtNum);
}

std::unordered_set<int> ParentReader::getRelationshipsByKey(int stmtNum) {
  return getChild(stmtNum);
}

bool ParentReader::hasRelationship(int stmt1, int stmt2) {
  return hasParent(stmt1, stmt2);
}