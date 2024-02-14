#pragma once

#include <memory>
#include "pkb/stores/entities/types/ReadStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

class ReadWriter: public IEntityWriter<int> {
private:
    std::shared_ptr<ReadStore> readStore;
public:
    explicit ReadWriter(std::shared_ptr<ReadStore> rs) : readStore(std::move(rs)) {}

    bool addEntity(int entity) override {
      return insertRead(entity);
    }

    void clear() override {
      readStore->clear();
    }

    bool insertRead(int stmtNum) {
      return readStore->addEntity(stmtNum);
    }
};
