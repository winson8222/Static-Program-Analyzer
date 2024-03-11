#pragma once

#include <memory>

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/AssignStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class AssignReader: public IEntityReader<int> {
private:
    std::shared_ptr<AssignStore> assignStore;
public:
    AssignReader(std::shared_ptr<AssignStore> store);

    bool isEmpty() const override;

    std::unordered_set<int> getAllEntities() const override;

    bool contains(int stmtNum) const override;

    // Custom methods
    /**
     * @brief Gets all statement numbers of "Assign" statements.
     * @return unordered_set<int>: The set of statement numbers of all "Assign" statements.
     */
    std::unordered_set<int> getAllAssigns() const;

    /**
     * @brief Checks if a specific "Assign" statement exists.
     * @param stmtNum The statement number to check.
     * @return true if the "Assign" statement exists, false otherwise.
     */
    bool hasAssign(int stmtNum) const;
};
// ai-gen end
