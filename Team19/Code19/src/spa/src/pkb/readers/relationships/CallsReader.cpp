#include "CallsReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
CallsReader::CallsReader(std::shared_ptr<CallsStore> store) : callsStore(std::move(store)) {}

// Inherited methods
bool CallsReader::isEmpty() {
    return callsStore->isEmpty();
}

std::unordered_map<std::string, std::unordered_set<std::string>> CallsReader::getKeyValueRelationships() {
    return callsStore->getKeyValueRelationships();
}

std::unordered_map<std::string, std::unordered_set<std::string>> CallsReader::getValueKeyRelationships() {
    return callsStore->getValueKeyRelationships();
}

std::unordered_set<std::string> CallsReader::getKeys() {
    return callsStore->getKeys();
}

std::unordered_set<std::string> CallsReader::getValues() {
    return callsStore->getValues();
}

std::unordered_set<std::string> CallsReader::getRelationshipsByKey(std::string key) {
    return callsStore->getRelationshipsByKey(key);
}

std::unordered_set<std::string> CallsReader::getRelationshipsByValue(std::string value) {
    return callsStore->getRelationshipsByValue(value);
}

bool CallsReader::hasRelationship(std::string key, std::string value) {
    return callsStore->hasRelationship(key, value);
}

// Custom methods
std::unordered_set<std::string> CallsReader::getDirectlyCalledProcedures(std::string caller) {
    return callsStore->getRelationshipsByKey(caller);
}

std::unordered_set<std::string> CallsReader::getDirectCallersOfProcedure(std::string callee) {
    return callsStore->getRelationshipsByValue(callee);
}

bool CallsReader::isDirectCaller(std::string caller, std::string callee) {
    return callsStore->hasRelationship(caller, callee);
}

std::unordered_set<std::string> CallsReader::getAllDirectCallers() {
    return callsStore->getKeys();
}

std::unordered_set<std::string> CallsReader::getAllDirectCallees() {
    return callsStore->getValues();
}

bool CallsReader::hasAnyDirectCalls(std::string caller) {
    return !callsStore->getRelationshipsByKey(caller).empty();
}

bool CallsReader::isDirectCallee(std::string callee) {
    return !callsStore->getRelationshipsByValue(callee).empty();
}
// ai-gen end
