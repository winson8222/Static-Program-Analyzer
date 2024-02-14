#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/WhileStore.h"

class WhileReader: public IEntityReader<int> {
private:
    std::shared_ptr<WhileStore> whileStore;
public:
    explicit WhileReader(std::shared_ptr<WhileStore> store) {
      whileStore = std::move(store);
    }

    bool isEmpty() const override {
        return whileStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllWhiles();
    }

    bool contains(int stmtNum) const override {
      return hasWhile(stmtNum);
    }

    std::unordered_set<int> getAllWhiles() const {
      return whileStore->getAllEntities();
    }

    bool hasWhile(int stmtNum) const {
      return whileStore->contains(stmtNum);
    }
};
