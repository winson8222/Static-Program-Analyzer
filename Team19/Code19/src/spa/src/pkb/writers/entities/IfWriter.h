#pragma once

#include <memory>
#include "pkb/stores/entities/types/IfStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class IfWriter: public IEntityWriter<int> {
private:
    std::shared_ptr<IfStore> ifStore;
public:
    explicit IfWriter(std::shared_ptr<IfStore> is) : ifStore(std::move(is)) {}

    bool addEntity(int entity) override {
      return insertIf(entity);
    }

    void clear() override {
      ifStore->clear();
    }

    /**
     * @brief Inserts an "If" statement into the store.
     * @param stmtNum The statement number of the if statement.
     * @return True if the if statement is successfully inserted, false otherwise.
     */
    bool insertIf(int stmtNum) {
      return ifStore->addEntity(stmtNum);
    }
};
// ai-gen end
