#pragma once

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/ModifiesPStore.h"

/**
 * @class ModifiesPReader
 * @brief Reader class for accessing "Modifies" relationships involving procedures.
 *
 * This class provides read-only access to the "Modifies" relationships where
 * procedures modify variables. It utilizes the ModifiesPStore to query these relationships.
 * Inherits from IRelationshipReader to provide a consistent interface for relationship queries.
 */
class ModifiesPReader : public IRelationshipReader<std::string, std::string> {
private:
    std::shared_ptr<ModifiesPStore> store; ///< Store containing "Modifies" relationships for procedures.

public:
    /**
     * Constructor for ModifiesPReader.
     * @param store A shared pointer to a ModifiesPStore instance.
     */
    explicit ModifiesPReader(std::shared_ptr<ModifiesPStore> store) : store(std::move(store)) {}

    // Documenting override functions to match the interface's expectations
    bool isEmpty() override {
        return store->isEmpty();
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> getKeyValueRelationships() override {
        return store->getKeyValueRelationships();
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> getValueKeyRelationships() override {
        return store->getValueKeyRelationships();
    }

    std::unordered_set<std::string> getRelationshipsByKey(const std::string& key) {
        return store->getRelationshipsByKey(key);
    }

    std::unordered_set<std::string> getRelationshipsByValue(const std::string& value) {
        return store->getRelationshipsByValue(value);
    }

    bool hasRelationship(const std::string& key, const std::string& value) {
        return store->hasRelationship(key, value);
    }

    std::unordered_set<std::string> getKeys() override {
        return store->getKeys();
    }

    std::unordered_set<std::string> getValues() override {
        return store->getValues();
    }
};