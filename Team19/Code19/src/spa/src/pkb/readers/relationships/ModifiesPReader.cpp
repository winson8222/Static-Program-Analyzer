#include "ModifiesPReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
ModifiesPReader::ModifiesPReader(std::shared_ptr<ModifiesPStore> store) : store(std::move(store)) {}

// Custom methods
std::unordered_set<std::string> ModifiesPReader::getAllVariablesModifiedByProc(const std::string& procName) {
  return store->getRelationshipsByKey(procName);
}

std::unordered_set<std::string> ModifiesPReader::getAllProcsThatModifyVariable(const std::string& varName) {
  return store->getRelationshipsByValue(varName);
}

bool ModifiesPReader::doesProcModifyVariable(const std::string& procName, const std::string& varName) {
  return store->hasRelationship(procName, varName);
}

std::unordered_set<std::string> ModifiesPReader::getAllProcsThatModifyAnyVariable() {
  return store->getKeys();
}

std::unordered_set<std::string> ModifiesPReader::getAllVariablesModifiedByAnyProc() {
  return store->getValues();
}

// Inherited methods
bool ModifiesPReader::isEmpty() {
  return store->isEmpty();
}

std::unordered_map<std::string, std::unordered_set<std::string>> ModifiesPReader::getKeyValueRelationships() {
return store->getKeyValueRelationships();
}

std::unordered_map<std::string, std::unordered_set<std::string>> ModifiesPReader::getValueKeyRelationships() {
  return store->getValueKeyRelationships();
}

std::unordered_set<std::string> ModifiesPReader::getRelationshipsByKey(std::string key) {
return store->getRelationshipsByKey(key);
}

std::unordered_set<std::string> ModifiesPReader::getRelationshipsByValue(std::string value) {
return store->getRelationshipsByValue(value);
}

bool ModifiesPReader::hasRelationship(std::string key, std::string value) {
return store->hasRelationship(key, value);
}

std::unordered_set<std::string> ModifiesPReader::getKeys() {
return store->getKeys();
}

std::unordered_set<std::string> ModifiesPReader::getValues() {
return store->getValues();
}