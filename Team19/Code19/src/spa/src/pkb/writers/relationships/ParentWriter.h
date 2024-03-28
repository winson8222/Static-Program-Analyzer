#pragma once

#include <memory>

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/ParentStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ParentWriter : public IRelationshipWriter<int, int> {
private:
    std::shared_ptr<ParentStore> parentStore;

public:
    explicit ParentWriter(std::shared_ptr<ParentStore> store);
    void addRelationship(int parent, int child) override;
    void clear() override;
    // Custom methods
    /**
     * @brief Adds a "Parent" relationship between a parent and a child.
     * @param parent The parent statement number.
     * @param child The child statement number.
     */
    void addParent(int parent, int child);
};
// ai-gen end
