#pragma once

#include <memory>

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/IfStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class IfReader: public IEntityReader<int> {
private:
    std::shared_ptr<IfStore> ifStore;
public:
    IfReader(std::shared_ptr<IfStore> store);

    bool isEmpty() const override;

    std::unordered_set<int> getAllEntities() const override;

    bool contains(int stmtNum) const override;

    // Custom methods
    /**
     * @brief Gets all statement numbers of "If" statements.
     * @return unordered_set<int>: The set of statement numbers of all "If" statements.
     */
    std::unordered_set<int> getAllIfs() const;

    /**
     * @brief Checks if a specific "If" statement exists.
     * @param stmtNum The statement number to check.
     * @return true if the "If" statement exists, false otherwise.
     */
    bool hasIf(int stmtNum) const;
};
// ai-gen end
