#pragma once

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/ModifiesSStore.h"

/**
 * @class ModifiesSReader
 * @brief Reader class for accessing "Modifies" relationships involving statements.
 *
 * This class provides read-only access to the "Modifies" relationships where
 * statements modify variables. It utilizes the ModifiesSStore to query these relationships.
 * Inherits from IRelationshipReader to provide a consistent interface for relationship queries.
 */

class ModifiesSReader : public IRelationshipReader<int, std::string> {
private:
    std::shared_ptr<ModifiesSStore> store;

public:
    explicit ModifiesSReader(std::shared_ptr<ModifiesSStore> store) : store(std::move(store)) {}

    bool isEmpty() override {
        return store->isEmpty();
    }

    std::unordered_map<int, std::unordered_set<std::string>> getKeyValueRelationships() override {
        return store->getKeyValueRelationships();
    }

    std::unordered_map<std::string, std::unordered_set<int>> getValueKeyRelationships() override {
        // This implementation needs to be adjusted if IRelationshipReader's signature expects this return type.
        // It might require rethinking how the data is stored or transforming the data to fit this requirement.
    }

    std::unordered_set<std::string> getRelationshipsByKey(int key) override {
        return store->getRelationshipsByKey(key);
    }

    std::unordered_set<int> getRelationshipsByValue(const std::string& value) override {
        return store->getRelationshipsByValue(value);
    }

    bool hasRelationship(int key, const std::string& value) override {
        return store->hasRelationship(key, value);
    }

    std::unordered_set<int> getKeys() override {
        return store->getKeys();
    }

    std::unordered_set<std::string> getValues() override {
        return store->getValues();
    }
};