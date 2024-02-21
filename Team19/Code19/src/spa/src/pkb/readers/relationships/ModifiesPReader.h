#pragma once

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/ModifiesPStore.h"

class ModifiesPReader : public IRelationshipReader<std::string, std::string> {
private:
    std::shared_ptr<ModifiesPStore> store;
public:
    explicit ModifiesPReader(std::shared_ptr<ModifiesPStore> store) : store(std::move(store)) {}

    // Custom methods
    /**
     * @brief Gets all the variables modified by a given procedure.
     * @param procName The procedure name to query.
     * @return unordered_set<string>: The set of variables modified by the given procedure.
     */
    std::unordered_set<std::string> getAllVariablesModifiedByProc(const std::string& procName) {
        return store->getRelationshipsByKey(procName);
    }

    /**
     * @brief Gets all the procedures that modify a given variable.
     * @param varName The variable name to query.
     * @return unordered_set<string>: The set of procedure names that modify the given variable.
     */
    std::unordered_set<std::string> getAllProcsThatModifyVariable(const std::string& varName) {
        return store->getRelationshipsByValue(varName);
    }

    /**
     * @brief Checks if a given procedure modifies a given variable.
     * @param procName The procedure name to query.
     * @param varName The variable name to query.
     * @return bool: True if the procedure modifies the variable, false otherwise.
     */
    bool doesProcModifyVariable(const std::string& procName, const std::string& varName) {
        return store->hasRelationship(procName, varName);
    }

    /**
     * @brief Gets all the procedures that modify any variable.
     * @return unordered_set<string>: The set of all procedure names that modify any variable.
     */
    std::unordered_set<std::string> getAllProcsThatModifyAnyVariable() {
        return store->getKeys();
    }

    /**
     * @brief Gets all the variables modified by any procedure.
     * @return unordered_set<string>: The set of all variables modified by any procedure.
     */
    std::unordered_set<std::string> getAllVariablesModifiedByAnyProc() {
        return store->getValues();
    }

    // Inherited methods
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
