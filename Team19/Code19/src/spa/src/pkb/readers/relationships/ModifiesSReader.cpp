#include "ModifiesSReader.h"

ModifiesSReader::ModifiesSReader(std::shared_ptr<ModifiesSStore> store) : store(std::move(store)) {}

bool ModifiesSReader::isEmpty() {
  return store->isEmpty();
}

int ModifiesSReader::getSize() {
  return store->getSize();
}

int ModifiesSReader::getRelationshipCountByKey(int stmtNum) {
  return store->getRelationshipCountByKey(stmtNum);
}

int ModifiesSReader::getRelationshipCountByValue(std::string varName) {
  return store->getRelationshipCountByValue(varName);
}

// Custom methods
std::unordered_set<std::string> ModifiesSReader::getAllVariablesModifiedByStmt(int stmtNum) {
  return store->getRelationshipsByKey(stmtNum);
}

std::unordered_set<int> ModifiesSReader::getAllStmtsThatModifyVariable(const std::string& varName) {
  return store->getRelationshipsByValue(varName);
}

bool ModifiesSReader::doesStmtModifyVariable(int stmtNum, const std::string& varName) {
  return store->hasRelationship(stmtNum, varName);
}

std::unordered_set<int> ModifiesSReader::getAllStmtsThatModifyAnyVariable() {
  return store->getKeys();
}

std::unordered_set<std::string> ModifiesSReader::getAllVariablesModifiedByAnyStmt() {
  return store->getValues();
}

// Inherited methods
std::unordered_map<int, std::unordered_set<std::string>> ModifiesSReader::getKeyValueRelationships() {
  return store->getKeyValueRelationships();
}

std::unordered_map<std::string, std::unordered_set<int>> ModifiesSReader::getValueKeyRelationships() {
  return store->getValueKeyRelationships();
}

std::unordered_set<std::string> ModifiesSReader::getRelationshipsByKey(int key) {
  return store->getRelationshipsByKey(key);
}

std::unordered_set<int> ModifiesSReader::getRelationshipsByValue(std::string value) {
  return store->getRelationshipsByValue(value);
}

bool ModifiesSReader::hasRelationship(int key, std::string value) {
  return store->hasRelationship(key, value);
}

std::unordered_set<int> ModifiesSReader::getKeys() {
  return store->getKeys();
}

std::unordered_set<std::string> ModifiesSReader::getValues() {
  return store->getValues();
}

