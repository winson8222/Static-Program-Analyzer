#include "UsesPReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
UsesPReader::UsesPReader(std::shared_ptr<UsesPStore> store) : store(std::move(store)) {}

// Custom methods
/**
 * @brief Gets all the variables used by a given procedure.
 * @param procName The procedure name to query.
 * @return unordered_set<string>: The set of variables used by the given procedure.
 */
std::unordered_set<std::string> UsesPReader::getAllVariablesUsedByProc(const std::string& procName) {
  return store->getRelationshipsByKey(procName);
}

std::unordered_set<std::string> UsesPReader::getAllProcsThatUseVariable(const std::string& varName) {
  return store->getRelationshipsByValue(varName);
}

bool UsesPReader::doesProcUseVariable(const std::string& procName, const std::string& varName) {
  return store->hasRelationship(procName, varName);
}

std::unordered_set<std::string> UsesPReader::getAllProcsThatUseAnyVariable() {
  return store->getKeys();
}

std::unordered_set<std::string> UsesPReader::getAllVariablesUsedByAnyProc() {
  return store->getValues();
}

// Inherited methods
bool UsesPReader::isEmpty() {
  return store->isEmpty();
}

std::unordered_map<std::string, std::unordered_set<std::string>> UsesPReader::getKeyValueRelationships() {
  return store->getKeyValueRelationships();
}

std::unordered_map<std::string, std::unordered_set<std::string>> UsesPReader::getValueKeyRelationships() {
  return store->getValueKeyRelationships();
}

std::unordered_set<std::string> UsesPReader::getRelationshipsByKey(std::string key) {
  return store->getRelationshipsByKey(key);
}

std::unordered_set<std::string> UsesPReader::getRelationshipsByValue(std::string value) {
  return store->getRelationshipsByValue(value);
}

bool UsesPReader::hasRelationship(std::string key, std::string value) {
  return store->hasRelationship(key, value);
}

std::unordered_set<std::string> UsesPReader::getKeys() {
  return store->getKeys();
}

std::unordered_set<std::string> UsesPReader::getValues() {
  return store->getValues();
}

int UsesPReader::getSize() {
  return store->getSize();
}

int UsesPReader::getRelationshipCountByKey(std::string key) {
    return store->getRelationshipCountByKey(key);
}

int UsesPReader::getRelationshipCountByValue(std::string value) {
    return store->getRelationshipCountByValue(value);
}
// ai-gen end
