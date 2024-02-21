#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/PrintStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class PrintReader: public IEntityReader<int> {
private:
    std::shared_ptr<PrintStore> printStore;
public:
    explicit PrintReader(std::shared_ptr<PrintStore> store) {
      printStore = std::move(store);
    }

    bool isEmpty() const override {
        return printStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllPrints();
    }

    bool contains(int stmtNum) const override {
      return hasPrint(stmtNum);
    }

    // Custom methods
    /**
     * @brief Gets all statement numbers of "Print" statements.
     * @return unordered_set<int>: The set of statement numbers of all "Print" statements.
     */
    std::unordered_set<int> getAllPrints() const {
      return printStore->getAllEntities();
    }

    /**
     * @brief Checks if a specific "Print" statement exists.
     * @param stmtNum The statement number to check.
     * @return true if the "Print" statement exists, false otherwise.
     */
    bool hasPrint(int stmtNum) const {
      return printStore->contains(stmtNum);
    }
};
// ai-gen end
