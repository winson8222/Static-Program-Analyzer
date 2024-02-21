#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/WhileStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class WhileReader: public IEntityReader<int> {
private:
    std::shared_ptr<WhileStore> whileStore;
public:
    explicit WhileReader(std::shared_ptr<WhileStore> store) {
      whileStore = std::move(store);
    }

    bool isEmpty() const override {
        return whileStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllWhiles();
    }

    bool contains(int stmtNum) const override {
      return hasWhile(stmtNum);
    }

    // Custom methods
    /**
     * @brief Gets all statement numbers of "While" statements.
     * @return unordered_set<int>: The set of statement numbers of all "While" statements.
     */
    std::unordered_set<int> getAllWhiles() const {
      return whileStore->getAllEntities();
    }

    /**
     * @brief Checks if a specific "While" statement exists.
     * @param stmtNum The statement number to check.
     * @return true if the "While" statement exists, false otherwise.
     */
    bool hasWhile(int stmtNum) const {
      return whileStore->contains(stmtNum);
    }
};
// ai-gen end
