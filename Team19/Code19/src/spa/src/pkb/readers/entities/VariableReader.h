#pragma once

#include <memory>

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/VariableStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class VariableReader: public IEntityReader<std::string> {
private:
    std::shared_ptr<VariableStore> variableStore;
public:
    VariableReader(std::shared_ptr<VariableStore> vs);
    bool isEmpty() const override;
    std::unordered_set<std::string> getAllEntities() const override;
    bool contains(std::string variable) const override;

    // Custom methods
    /**
     * @brief Gets all variable names.
     * @return unordered_set<string>: The set of all variable names.
     */
    std::unordered_set<std::string> getAllVariables() const;

    /**
     * @brief Checks if a specific variable exists.
     * @param variable The variable name to check.
     * @return true if the variable exists, false otherwise.
     */
    bool hasVariable(std::string variable) const;
};
// ai-gen end
