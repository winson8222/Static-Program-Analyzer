#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/ConstantStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ConstantReader: public IEntityReader<int> {
private:
    std::shared_ptr<ConstantStore> constantStore;
public:
    explicit ConstantReader(std::shared_ptr<ConstantStore> store) {
      constantStore = std::move(store);
    }

    bool isEmpty() const override {
        return constantStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllConstants();
    }

    bool contains(int stmtNum) const override {
      return hasConstant(stmtNum);
    }

    std::unordered_set<int> getAllConstants() const {
      return constantStore->getAllEntities();
    }

    bool hasConstant(int constant) const {
      return constantStore->contains(constant);
    }
};
// ai-gen end
