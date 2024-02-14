#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/CallStore.h"

class CallReader: public IEntityReader<int> {
private:
    std::shared_ptr<CallStore> callStore;
public:
    explicit CallReader(std::shared_ptr<CallStore> store) {
      callStore = std::move(store);
    }

    bool isEmpty() const override {
        return callStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllCalls();
    }

    bool contains(int stmtNum) const override {
      return hasCall(stmtNum);
    }

    std::unordered_set<int> getAllCalls() const {
      return callStore->getAllEntities();
    }

    bool hasCall(int stmtNum) const {
      return callStore->contains(stmtNum);
    }
};
