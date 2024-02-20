#pragma once

#include <memory>
#include "pkb/stores/entities/types/PrintStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class PrintWriter: public IEntityWriter<int> {
private:
    std::shared_ptr<PrintStore> printStore;
public:
    explicit PrintWriter(std::shared_ptr<PrintStore> ps) : printStore(std::move(ps)) {}

    bool addEntity(int entity) override {
      return insertPrint(entity);
    }

    void clear() override {
      printStore->clear();
    }

    /**
     * @brief Inserts a "Print" statement into the store.
     * @param stmtNum The statement number of the print statement.
     * @return True if the print statement is successfully inserted, false otherwise.
     */
    bool insertPrint(int stmtNum) {
      return printStore->addEntity(stmtNum);
    }
};
