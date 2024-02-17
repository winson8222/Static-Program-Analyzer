#pragma once

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/UsesSStore.h"
#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>

/**
 * Provides read-only access to the Uses relationships for statements.
 * Specifically, it accesses data about which statements use which variables.
 */
class UsesSReader : public IRelationshipReader<int, std::string> {
private:
    std::shared_ptr<UsesSStore> store; // Store for Uses relationships involving statements.

public:
    explicit UsesSReader(std::shared_ptr<UsesSStore> store) : store(std::move(store)) {}

    bool isEmpty() override {
        return store->isEmpty();
    }

    std::unordered_map<int, std::unordered_set<std::string>> getKeyValueRelationships() override {
        return store->getKeyValueRelationships();
    }

    std::unordered_map<std::string, std::unordered_set<int>> getValueKeyRelationships() override {
        return store->getValueKeyRelationships();
    }

    std::unordered_set<std::string> getRelationshipsByKey(int key) override {
        return store->getRelationshipsByKey(key);
    }

    std::unordered_set<int> getRelationshipsByValue(const std::string& value) {
        return store->getRelationshipsByValue(value);
    }

    bool hasRelationship(int key, const std::string& value) {
        return store->hasRelationship(key, value);
    }

    std::unordered_set<int> getKeys() override {
        return store->getKeys();
    }

    std::unordered_set<std::string> getValues() override {
        return store->getValues();
    }
};
