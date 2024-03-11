#include "AffectsReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
AffectsReader::AffectsReader(std::shared_ptr<AffectsStore> store) : affectsStore(std::move(store)) {}

bool AffectsReader::isEmpty() {
    return affectsStore->isEmpty();
}

std::unordered_map<int, std::unordered_set<int>> AffectsReader::getKeyValueRelationships() {
    return affectsStore->getKeyValueRelationships();
}

std::unordered_map<int, std::unordered_set<int>> AffectsReader::getValueKeyRelationships() {
    return affectsStore->getValueKeyRelationships();
}

std::unordered_set<int> AffectsReader::getKeys() {
    return affectsStore->getKeys();
}

std::unordered_set<int> AffectsReader::getValues() {
    return affectsStore->getValues();
}

std::unordered_set<int> AffectsReader::getRelationshipsByKey(int key) {
    return affectsStore->getRelationshipsByKey(key);
}

std::unordered_set<int> AffectsReader::getRelationshipsByValue(int value) {
    return affectsStore->getRelationshipsByValue(value);
}

bool AffectsReader::hasRelationship(int key, int value) {
    return affectsStore->hasRelationship(key, value);
}

std::unordered_set<int> AffectsReader::getAllAffecting() {
    return affectsStore->getKeys();
}

std::unordered_set<int> AffectsReader::getAllAffected() {
    return affectsStore->getValues();
}

std::unordered_set<int> AffectsReader::getAffecting(int value) {
    return affectsStore->getRelationshipsByValue(value);
}

std::unordered_set<int> AffectsReader::getAffected(int key) {
    return affectsStore->getRelationshipsByKey(key);
}

bool AffectsReader::hasAffects(int key, int value) {
    return affectsStore->hasRelationship(key, value);
}
// ai-gen end
