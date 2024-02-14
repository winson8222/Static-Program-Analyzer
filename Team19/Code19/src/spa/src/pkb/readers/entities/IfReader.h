#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/IfStore.h"

class IfReader: public IEntityReader<int> {
private:
    std::shared_ptr<IfStore> ifStore;
public:
    explicit IfReader(std::shared_ptr<IfStore> store) {
      ifStore = std::move(store);
    }

    bool isEmpty() const override {
        return ifStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllIfs();
    }

    bool contains(int stmtNum) const override {
      return hasIf(stmtNum);
    }

    std::unordered_set<int> getAllIfs() const {
      return ifStore->getAllEntities();
    }

    bool hasIf(int stmtNum) const {
      return ifStore->contains(stmtNum);
    }
};
