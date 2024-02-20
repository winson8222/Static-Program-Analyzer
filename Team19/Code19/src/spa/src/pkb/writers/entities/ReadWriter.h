#pragma once

#include <memory>
#include "pkb/stores/entities/types/ReadStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
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

    /**
     * @brief Inserts a "Read" statement into the store.
     * @param stmtNum The statement number of the read statement.
     * @return True if the read statement is successfully inserted, false otherwise.
     */
    bool insertRead(int stmtNum) {
      return readStore->addEntity(stmtNum);
    }
};
// ai-gen end
