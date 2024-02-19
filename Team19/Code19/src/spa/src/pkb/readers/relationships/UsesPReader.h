#pragma once

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/UsesPStore.h"
#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>

/**
 * Provides read-only access to the Uses relationships for procedures.
 * Specifically, it accesses data about which procedures use which variables.
 */
class UsesPReader : public IRelationshipReader<std::string, std::string> {
private:
    std::shared_ptr<UsesPStore> store; // Store for Uses relationships involving procedures.

public:
    explicit UsesPReader(std::shared_ptr<UsesPStore> store) : store(std::move(store)) {}

    bool isEmpty() override {
        return store->isEmpty();
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> getKeyValueRelationships() override {
        return store->getKeyValueRelationships();
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> getValueKeyRelationships() override {
        return store->getValueKeyRelationships();
    }

    std::unordered_set<std::string> getRelationshipsByKey(std::string key) override {
        return store->getRelationshipsByKey(key);
    }

    std::unordered_set<std::string> getRelationshipsByValue(std::string value) override {
        return store->getRelationshipsByValue(value);
    }

    bool hasRelationship(std::string key, std::string value) override {
        return store->hasRelationship(key, value);
    }

    std::unordered_set<std::string> getKeys() override {
        return store->getKeys();
    }

    std::unordered_set<std::string> getValues() override {
        return store->getValues();
    }
};