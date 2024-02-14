#pragma once

#include <memory>
#include "pkb/stores/entities/types/IfStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

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

    bool insertIf(int stmtNum) {
      return ifStore->addEntity(stmtNum);
    }
};
