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

    bool insertStatement(int stmtNum) {
      return statementStore->addEntity(stmtNum);
    }
};
// ai-gen end
