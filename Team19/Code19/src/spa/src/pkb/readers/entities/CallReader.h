#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/CallStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class CallReader: public IEntityReader<int> {
private:
    std::shared_ptr<CallStore> callStore;
public:
    explicit CallReader(std::shared_ptr<CallStore> store) {
      callStore = std::move(store);
    }

    bool isEmpty() const override {
        return callStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllCalls();
    }

    bool contains(int stmtNum) const override {
      return hasCall(stmtNum);
    }

    // Custom methods
    /**
     * @brief Gets all statement numbers of "Call" statements.
     * @return unordered_set<int>: The set of statement numbers of all "Call" statements.
     */
    std::unordered_set<int> getAllCalls() const {
      return callStore->getAllEntities();
    }

    /**
     * @brief Checks if a specific "Call" statement exists.
     * @param stmtNum The statement number to check.
     * @return true if the "Call" statement exists, false otherwise.
     */
    bool hasCall(int stmtNum) const {
      return callStore->contains(stmtNum);
    }
};
// ai-gen end
