#pragma once

#include <memory>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "pkb/stores/relationships/IRelationshipReader.h"
#include "pkb/stores/relationships/types/UsesSStore.h"

class UsesSReader : public IRelationshipReader<int, std::string> {
private:
    std::shared_ptr<UsesSStore> store; // Store for Uses relationships involving statements.

public:
    UsesSReader(std::shared_ptr<UsesSStore> store);

    // Custom methods
    /**
     * @brief Gets all the variables used by a given statement.
     * @param stmtNum The statement number to query.
     * @return unordered_set<string>: The set of variables used by the given statement.
     */
    std::unordered_set<std::string> getAllVariablesUsedByStmt(int stmtNum);

    /**
     * @brief Gets all the statements that use a given variable.
     * @param varName The variable name to query.
     * @return unordered_set<int>: The set of statement numbers that use the given variable.
     */
    std::unordered_set<int> getAllStmtsThatUseVariable(const std::string& varName);

    /**
     * @brief Checks if a given statement uses a given variable.
     * @param stmtNum The statement number to query.
     * @param varName The variable name to query.
     * @return bool: True if the statement uses the variable, false otherwise.
     */
    bool doesStmtUseVariable(int stmtNum, const std::string& varName);

    /**
     * @brief Gets all the statements that use any variable.
     * @return unordered_set<int>: The set of all statement numbers that use any variable.
     */
    std::unordered_set<int> getAllStmtsThatUseAnyVariable();

    /**
     * @brief Gets all the variables used by any statement.
     * @return unordered_set<string>: The set of all variables used by any statement.
     */
    std::unordered_set<std::string> getAllVariablesUsedByAnyStmt();

    // Inherited methods
    bool isEmpty() override;
    std::unordered_map<int, std::unordered_set<std::string>> getKeyValueRelationships() override;
    std::unordered_map<std::string, std::unordered_set<int>> getValueKeyRelationships() override;
    std::unordered_set<std::string> getRelationshipsByKey(int key) override;
    std::unordered_set<int> getRelationshipsByValue(std::string value) override;
    bool hasRelationship(int key, std::string value) override;
    std::unordered_set<int> getKeys() override;
    std::unordered_set<std::string> getValues() override;
};
