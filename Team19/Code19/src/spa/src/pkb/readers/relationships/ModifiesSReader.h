#pragma once

#include <memory>

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
	ModifiesSReader(std::shared_ptr<ModifiesSStore> store);

    bool isEmpty() override;
    // Custom methods
    /**
     * @brief Gets all the variables modified by a given statement.
     * @param stmtNum The statement number to query.
     * @return unordered_set<string>: The set of variables modified by the given statement.
     */
    std::unordered_set<std::string> getAllVariablesModifiedByStmt(int stmtNum);

    /**
     * @brief Gets all the statements that modify a given variable.
     * @param varName The variable name to query.
     * @return unordered_set<int>: The set of statement numbers that modify the given variable.
     */
    std::unordered_set<int> getAllStmtsThatModifyVariable(const std::string& varName);

    /**
     * @brief Checks if a given statement modifies a given variable.
     * @param stmtNum The statement number to query.
     * @param varName The variable name to query.
     * @return bool: True if the statement modifies the variable, false otherwise.
     */
    bool doesStmtModifyVariable(int stmtNum, const std::string& varName);

    /**
     * @brief Gets all the statements that modify any variable.
     * @return unordered_set<int>: The set of all statement numbers that modify any variable.
     */
    std::unordered_set<int> getAllStmtsThatModifyAnyVariable();

    /**
     * @brief Gets all the variables modified by any statement.
     * @return unordered_set<string>: The set of all variables modified by any statement.
     */
    std::unordered_set<std::string> getAllVariablesModifiedByAnyStmt();

    // Inherited methods
    std::unordered_map<int, std::unordered_set<std::string>> getKeyValueRelationships() override;

    std::unordered_map<std::string, std::unordered_set<int>> getValueKeyRelationships() override;

    std::unordered_set<std::string> getRelationshipsByKey(int key) override;

    std::unordered_set<int> getRelationshipsByValue(std::string value) override;

    bool hasRelationship(int key, std::string value) override;

    std::unordered_set<int> getKeys() override;

    std::unordered_set<std::string> getValues() override;
};
