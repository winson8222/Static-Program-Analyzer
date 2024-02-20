#pragma once

#include <memory>
#include "pkb/stores/entities/types/CallStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class CallWriter: public IEntityWriter<int> {
private:
    std::shared_ptr<CallStore> callStore;
public:
    explicit CallWriter(std::shared_ptr<CallStore> cs) : callStore(std::move(cs)) {}

    bool addEntity(int entity) override {
      return insertCall(entity);
    }

    void clear() override {
      callStore->clear();
    }

    /**
     * @brief Inserts a "Call" statement into the store.
     * @param stmtNum The statement number of the call statement.
     * @return True if the call statement is successfully inserted, false otherwise.
     */
    bool insertCall(int stmtNum) {
      return callStore->addEntity(stmtNum);
    }
};
// ai-gen end
