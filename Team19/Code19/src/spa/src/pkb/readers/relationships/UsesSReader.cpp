#include "UsesSReader.h"

UsesSReader::UsesSReader(std::shared_ptr<UsesSStore> store) : store(std::move(store)) {}

std::unordered_set<std::string> UsesSReader::getAllVariablesUsedByStmt(int stmtNum) {
  return store->getRelationshipsByKey(stmtNum);
}

std::unordered_set<int> UsesSReader::getAllStmtsThatUseVariable(const std::string& varName) {
  return store->getRelationshipsByValue(varName);
}

bool UsesSReader::doesStmtUseVariable(int stmtNum, const std::string& varName) {
  return store->hasRelationship(stmtNum, varName);
}

std::unordered_set<int> UsesSReader::getAllStmtsThatUseAnyVariable() {
  return store->getKeys();
}

std::unordered_set<std::string> UsesSReader::getAllVariablesUsedByAnyStmt() {
  return store->getValues();
}

bool UsesSReader::isEmpty() {
  return store->isEmpty();
}

std::unordered_map<int, std::unordered_set<std::string>> UsesSReader::getKeyValueRelationships() {
  return store->getKeyValueRelationships();
}

std::unordered_map<std::string, std::unordered_set<int>> UsesSReader::getValueKeyRelationships() {
  return store->getValueKeyRelationships();
}

std::unordered_set<std::string> UsesSReader::getRelationshipsByKey(int key) {
  return store->getRelationshipsByKey(key);
}

std::unordered_set<int> UsesSReader::getRelationshipsByValue(std::string value) {
  return store->getRelationshipsByValue(value);
}

bool UsesSReader::hasRelationship(int key, std::string value) {
  return store->hasRelationship(key, value);
}

std::unordered_set<int> UsesSReader::getKeys() {
  return store->getKeys();
}

std::unordered_set<std::string> UsesSReader::getValues() {
  return store->getValues();
}

int UsesSReader::getSize() {
  return store->getSize();
}

int UsesSReader::getRelationshipCountByKey(int key) {
    return store->getRelationshipCountByKey(key);
}

int UsesSReader::getRelationshipCountByValue(std::string value) {
    return store->getRelationshipCountByValue(value);
}
// ai-gen end
