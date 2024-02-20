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

    // Custom methods
    /**
     * @brief Adds a "ParentT" relationship between a parent and a child.
     * @param parent The parent statement number.
     * @param child The child statement number.
     */
    void addParentT(int parent, int child) {
        parentTStore->addRelationship(parent, child);
    }
};
// ai-gen end
