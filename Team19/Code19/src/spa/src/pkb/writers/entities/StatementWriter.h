#pragma once

#include <memory>
#include "pkb/stores/entities/types/StatementStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class StatementWriter: public IEntityWriter<int> {
private:
    std::shared_ptr<StatementStore> statementStore;
public:
    explicit StatementWriter(std::shared_ptr<StatementStore> ss) : statementStore(std::move(ss)) {}

    bool addEntity(int entity) override {
      return insertStatement(entity);
    }

    void clear() override {
      statementStore->clear();
    }

    /**
     * @brief Inserts a statement into the store.
     * @param stmtNum The statement number to be inserted.
     * @return True if the statement is successfully inserted, false otherwise.
     */
    bool insertStatement(int stmtNum) {
      return statementStore->addEntity(stmtNum);
    }
};
// ai-gen end
