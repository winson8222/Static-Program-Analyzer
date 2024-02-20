#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/StatementStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class StatementReader: public IEntityReader<int> {
private:
    std::shared_ptr<StatementStore> statementStore;
public:
    explicit StatementReader(std::shared_ptr<StatementStore> store) {
      statementStore = std::move(store);
    }

    bool isEmpty() const override {
        return statementStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllStatements();
    }

    bool contains(int stmtNum) const override {
      return hasProcedure(stmtNum);
    }

    std::unordered_set<int> getAllStatements() const {
      return statementStore->getAllEntities();
    }

    bool hasProcedure(int stmtNum) const {
      return statementStore->contains(stmtNum);
    }
};
// ai-gen end
