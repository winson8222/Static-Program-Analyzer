#pragma once

#include "memory"

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/CallStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class CallReader: public IEntityReader<int> {
private:
    std::shared_ptr<CallStore> callStore;
public:
    CallReader(std::shared_ptr<CallStore> store);
    bool isEmpty() const override;

    std::unordered_set<int> getAllEntities() const override;

    bool contains(int stmtNum) const override;
    // Custom methods
    /**
     * @brief Gets all statement numbers of "Call" statements.
     * @return unordered_set<int>: The set of statement numbers of all "Call" statements.
     */
    std::unordered_set<int> getAllCalls() const;

    /**
     * @brief Checks if a specific "Call" statement exists.
     * @param stmtNum The statement number to check.
     * @return true if the "Call" statement exists, false otherwise.
     */
    bool hasCall(int stmtNum) const;
};
// ai-gen end
