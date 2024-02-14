#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/PrintStore.h"

class PrintReader: public IEntityReader<int> {
private:
    std::shared_ptr<PrintStore> printStore;
public:
    explicit PrintReader(std::shared_ptr<PrintStore> store) {
      printStore = std::move(store);
    }

    bool isEmpty() const override {
        return printStore->isEmpty();
    }

    std::unordered_set<int> getAllEntities() const override {
        return getAllPrints();
    }

    bool contains(int stmtNum) const override {
      return hasPrint(stmtNum);
    }

    std::unordered_set<int> getAllPrints() const {
      return printStore->getAllEntities();
    }

    bool hasPrint(int stmtNum) const {
      return printStore->contains(stmtNum);
    }
};
