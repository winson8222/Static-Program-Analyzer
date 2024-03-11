#include "CallsTReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
CallsTReader::CallsTReader(std::shared_ptr<CallsTStore> store) : callsTStore(std::move(store)) {}

bool CallsTReader::isEmpty() {
    return callsTStore->isEmpty();
}

std::unordered_map<std::string, std::unordered_set<std::string>> CallsTReader::getKeyValueRelationships() {
    return callsTStore->getKeyValueRelationships();
}

std::unordered_map<std::string, std::unordered_set<std::string>> CallsTReader::getValueKeyRelationships() {
    return callsTStore->getValueKeyRelationships();
}

std::unordered_set<std::string> CallsTReader::getKeys() {
    return callsTStore->getKeys();
}

std::unordered_set<std::string> CallsTReader::getValues() {
    return callsTStore->getValues();
}

std::unordered_set<std::string> CallsTReader::getRelationshipsByKey(std::string key) {
    return callsTStore->getRelationshipsByKey(key);
}

std::unordered_set<std::string> CallsTReader::getRelationshipsByValue(std::string value) {
    return callsTStore->getRelationshipsByValue(value);
}

bool CallsTReader::hasRelationship(std::string key, std::string value) {
    return callsTStore->hasRelationship(key, value);
}

// Transitive-specific methods leveraging the underlying CallsTStore
std::unordered_set<std::string> CallsTReader::getTransitivelyCalledProcedures(std::string key) {
    return callsTStore->getRelationshipsByKey(key);
}

std::unordered_set<std::string> CallsTReader::getTransitiveCallersOfProcedure(std::string value) {
    return callsTStore->getRelationshipsByValue(value);
}

bool CallsTReader::isTransitiveCaller(std::string key, std::string value) {
    return callsTStore->hasRelationship(key, value);
}

std::unordered_set<std::string> CallsTReader::getAllTransitiveCallers() {
    return callsTStore->getKeys();
}

std::unordered_set<std::string> CallsTReader::getAllTransitiveCallees() {
    return callsTStore->getValues();
}

bool CallsTReader::hasAnyTransitiveCalls(std::string key) {
    // Checks if the specified key has any associated values in the transitive call relationships
    return !callsTStore->getRelationshipsByKey(key).empty();
}

bool CallsTReader::isTransitiveCallee(std::string value) {
    // Checks if the specified value is associated with any keys in the transitive call relationships
    return !callsTStore->getRelationshipsByValue(value).empty();
}
// ai-gen end