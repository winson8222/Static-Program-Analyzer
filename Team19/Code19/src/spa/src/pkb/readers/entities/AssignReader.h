#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/AssignStore.h"
#include <memory>

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class AssignReader: public IEntityReader<int> {
private:
    std::shared_ptr<AssignStore> assignStore;
public:
    explicit AssignReader(std::shared_ptr<AssignStore> store) {
        assignStore = std::move(store);
    }

    bool isEmpty() const override {
        return assignStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllAssigns();
    }

    bool contains(int stmtNum) const override {
      return hasAssign(stmtNum);
    }

    // Custom methods
    /**
     * @brief Gets all statement numbers of "Assign" statements.
     * @return unordered_set<int>: The set of statement numbers of all "Assign" statements.
     */
    std::unordered_set<int> getAllAssigns() const {
      return assignStore->getAllEntities();
    }

    /**
     * @brief Checks if a specific "Assign" statement exists.
     * @param stmtNum The statement number to check.
     * @return true if the "Assign" statement exists, false otherwise.
     */
    bool hasAssign(int stmtNum) const {
      return assignStore->contains(stmtNum);
    }
};
// ai-gen end
