#pragma once

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/ParentStore.h"
#include <memory>

class ParentWriter : public IRelationshipWriter<int, int> {
private:
    std::shared_ptr<ParentStore> parentStore;

public:
    explicit ParentWriter(std::shared_ptr<ParentStore> store) : parentStore(std::move(store)) {}

    void addRelationship(int parent, int child) override {
        addParent(parent, child);
    }

    void clear() override {
        parentStore->clear();
    }

    void addParent(int parent, int child) {
        parentStore->addRelationship(parent, child);
    }
};
