#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/ReadStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ReadReader: public IEntityReader<int> {
private:
    std::shared_ptr<ReadStore> readStore;
public:
    explicit ReadReader(std::shared_ptr<ReadStore> store) {
      readStore = std::move(store);
    }

    bool isEmpty() const override {
        return readStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllReads();
    }

    bool contains(int stmtNum) const override {
      return hasRead(stmtNum);
    }

    std::unordered_set<int> getAllReads() const {
      return readStore->getAllEntities();
    }

    bool hasRead(int stmtNum) const {
      return readStore->contains(stmtNum);
    }
};
// ai-gen end
