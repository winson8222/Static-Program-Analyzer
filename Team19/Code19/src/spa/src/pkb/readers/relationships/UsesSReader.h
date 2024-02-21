#pragma once

#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/UsesSStore.h"
#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>

class UsesSReader : public IRelationshipReader<int, std::string> {
private:
    std::shared_ptr<UsesSStore> store; // Store for Uses relationships involving statements.

public:
    explicit UsesSReader(std::shared_ptr<UsesSStore> store) : store(std::move(store)) {}

    // Custom methods
    /**
     * @brief Gets all the variables used by a given statement.
     * @param stmtNum The statement number to query.
     * @return unordered_set<string>: The set of variables used by the given statement.
     */
    std::unordered_set<std::string> getAllVariablesUsedByStmt(int stmtNum) {
      return store->getRelationshipsByKey(stmtNum);
    }

    /**
     * @brief Gets all the statements that use a given variable.
     * @param varName The variable name to query.
     * @return unordered_set<int>: The set of statement numbers that use the given variable.
     */
    std::unordered_set<int> getAllStmtsThatUseVariable(const std::string& varName) {
      return store->getRelationshipsByValue(varName);
    }

    /**
     * @brief Checks if a given statement uses a given variable.
     * @param stmtNum The statement number to query.
     * @param varName The variable name to query.
     * @return bool: True if the statement uses the variable, false otherwise.
     */
    bool doesStmtUseVariable(int stmtNum, const std::string& varName) {
      return store->hasRelationship(stmtNum, varName);
    }

    /**
     * @brief Gets all the statements that use any variable.
     * @return unordered_set<int>: The set of all statement numbers that use any variable.
     */
    std::unordered_set<int> getAllStmtsThatUseAnyVariable() {
      return store->getKeys();
    }

    /**
     * @brief Gets all the variables used by any statement.
     * @return unordered_set<string>: The set of all variables used by any statement.
     */
    std::unordered_set<std::string> getAllVariablesUsedByAnyStmt() {
      return store->getValues();
    }

    // Inherited methods
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
