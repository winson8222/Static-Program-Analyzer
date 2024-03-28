#pragma once

#include <memory>

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/ParentTStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ParentTWriter : public IRelationshipWriter<int, int> {
private:
    std::shared_ptr<ParentTStore> parentTStore;

public:
    explicit ParentTWriter(std::shared_ptr<ParentTStore> store);
    void addRelationship(int parent, int child) override;
    void clear() override;
    // Custom methods
    /**
     * @brief Adds a "ParentT" relationship between a parent and a child.
     * @param parent The parent statement number.
     * @param child The child statement number.
     */
    void addParentT(int parent, int child);
};
// ai-gen end
