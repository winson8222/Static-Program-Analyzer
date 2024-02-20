#pragma once

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/ParentTStore.h"
#include <memory>

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ParentTWriter : public IRelationshipWriter<int, int> {
private:
    std::shared_ptr<ParentTStore> parentTStore;

public:
    explicit ParentTWriter(std::shared_ptr<ParentTStore> store) : parentTStore(std::move(store)) {}

    void addRelationship(int parent, int child) override {
        addParentT(parent, child);
    }

    void clear() override {
        parentTStore->clear();
    }

    void addParentT(int parent, int child) {
        parentTStore->addRelationship(parent, child);
    }
};
// ai-gen end
