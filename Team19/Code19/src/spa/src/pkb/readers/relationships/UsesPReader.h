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
    UsesPReader(std::shared_ptr<UsesPStore> store);

    // Custom methods
    /**
     * @brief Gets all the variables used by a given procedure.
     * @param procName The procedure name to query.
     * @return unordered_set<string>: The set of variables used by the given procedure.
     */
    std::unordered_set<std::string> getAllVariablesUsedByProc(const std::string& procName);

    /**
     * @brief Gets all the procedures that use a given variable.
     * @param varName The variable name to query.
     * @return unordered_set<string>: The set of procedure names that use the given variable.
     */
    std::unordered_set<std::string> getAllProcsThatUseVariable(const std::string& varName);

    /**
     * @brief Checks if a given procedure uses a given variable.
     * @param procName The procedure name to query.
     * @param varName The variable name to query.
     * @return bool: True if the procedure uses the variable, false otherwise.
     */
    bool doesProcUseVariable(const std::string& procName, const std::string& varName);

    /**
     * @brief Gets all the procedures that use any variable.
     * @return unordered_set<string>: The set of all procedure names that use any variable.
     */
    std::unordered_set<std::string> getAllProcsThatUseAnyVariable();

    /**
     * @brief Gets all the variables used by any procedure.
     * @return unordered_set<string>: The set of all variables used by any procedure.
     */
    std::unordered_set<std::string> getAllVariablesUsedByAnyProc();

    // Inherited methods
    bool isEmpty() override;
    std::unordered_map<std::string, std::unordered_set<std::string>> getKeyValueRelationships() override;
    std::unordered_map<std::string, std::unordered_set<std::string>> getValueKeyRelationships() override;
    std::unordered_set<std::string> getRelationshipsByKey(std::string key) override;
    std::unordered_set<std::string> getRelationshipsByValue(std::string value) override;
    bool hasRelationship(std::string key, std::string value) override;
    std::unordered_set<std::string> getKeys() override;
    std::unordered_set<std::string> getValues() override;
};