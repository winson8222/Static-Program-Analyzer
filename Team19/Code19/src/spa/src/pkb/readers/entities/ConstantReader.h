#pragma once

#include <memory>

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/ConstantStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ConstantReader: public IEntityReader<int> {
private:
    std::shared_ptr<ConstantStore> constantStore;
public:
    ConstantReader(std::shared_ptr<ConstantStore> store);

    bool isEmpty() const override;
    std::unordered_set<int> getAllEntities() const override;

    bool contains(int stmtNum) const override;

    // Custom methods
    /**
     * @brief Gets all constant values.
     * @return unordered_set<int>: The set of all constant values.
     */
    std::unordered_set<int> getAllConstants() const;

    /**
     * @brief Checks if a specific constant exists.
     * @param constant The constant value to check.
     * @return true if the constant exists, false otherwise.
     */
    bool hasConstant(int constant) const;
};
// ai-gen end
