#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/AssignStore.h"
#include <memory>

class AssignReader: public IEntityReader<int> {
private:
    std::shared_ptr<AssignStore> assignStore;
public:
    explicit AssignReader(std::shared_ptr<AssignStore> store) {
        assignStore = std::move(store);
    }

    bool isEmpty() const override {
        return assignStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllAssigns();
    }

    bool contains(int stmtNum) const override {
      return hasAssign(stmtNum);
    }

    std::unordered_set<int> getAllAssigns() const {
      return assignStore->getAllEntities();
    }

    bool hasAssign(int stmtNum) const {
      return assignStore->contains(stmtNum);
    }
};
