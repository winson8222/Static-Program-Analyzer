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

    // Custom methods
    /**
     * @brief Gets all the variables modified by a given statement.
     * @param stmtNum The statement number to query.
     * @return unordered_set<string>: The set of variables modified by the given statement.
     */
    std::unordered_set<std::string> getAllVariablesModifiedByStmt(int stmtNum) {
        return store->getRelationshipsByKey(stmtNum);
    }

    /**
     * @brief Gets all the statements that modify a given variable.
     * @param varName The variable name to query.
     * @return unordered_set<int>: The set of statement numbers that modify the given variable.
     */
    std::unordered_set<int> getAllStmtsThatModifyVariable(const std::string& varName) {
        return store->getRelationshipsByValue(varName);
    }

    /**
     * @brief Checks if a given statement modifies a given variable.
     * @param stmtNum The statement number to query.
     * @param varName The variable name to query.
     * @return bool: True if the statement modifies the variable, false otherwise.
     */
    bool doesStmtModifyVariable(int stmtNum, const std::string& varName) {
        return store->hasRelationship(stmtNum, varName);
    }

    /**
     * @brief Gets all the statements that modify any variable.
     * @return unordered_set<int>: The set of all statement numbers that modify any variable.
     */
    std::unordered_set<int> getAllStmtsThatModifyAnyVariable() {
        return store->getKeys();
    }

    /**
     * @brief Gets all the variables modified by any statement.
     * @return unordered_set<string>: The set of all variables modified by any statement.
     */
    std::unordered_set<std::string> getAllVariablesModifiedByAnyStmt() {
        return store->getValues();
    }

    // Inherited methods
    std::unordered_map<int, std::unordered_set<std::string>> getKeyValueRelationships() override {
        return store->getKeyValueRelationships();
    }

    std::unordered_map<std::string, std::unordered_set<int>> getValueKeyRelationships() override {
        return store->getValueKeyRelationships();
    }

    std::unordered_set<std::string> getRelationshipsByKey(int key) override {
        return store->getRelationshipsByKey(key);
    }

    std::unordered_set<int> getRelationshipsByValue(std::string value) override {
        return store->getRelationshipsByValue(value);
    }

    bool hasRelationship(int key, std::string value) override {
        return store->hasRelationship(key, value);
    }

    std::unordered_set<int> getKeys() override {
        return store->getKeys();
    }

    std::unordered_set<std::string> getValues() override {
        return store->getValues();
    }
};
