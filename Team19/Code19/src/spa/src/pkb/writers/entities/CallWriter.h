#pragma once

#include <memory>
#include "pkb/stores/entities/types/CallStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

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

    bool insertCall(int stmtNum) {
      return callStore->addEntity(stmtNum);
    }
};
