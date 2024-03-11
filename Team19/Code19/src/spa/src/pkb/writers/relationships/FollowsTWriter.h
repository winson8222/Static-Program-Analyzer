#pragma once

#include <memory>

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/FollowsTStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class FollowsTWriter : public IRelationshipWriter<int, int> {
private:
    std::shared_ptr<FollowsTStore> followsTStore;

public:
    FollowsTWriter(std::shared_ptr<FollowsTStore> store);

    void addRelationship(int precedingStmt, int followingStmt) override;

    void clear() override;
    // Custom methods
    /**
     * @brief Adds a "FollowsT" relationship between a preceding statement and a following statement.
     * @param stmtNum The statement number of the preceding statement.
     * @param followingStmt The statement number of the following statement.
     */
    void addFollowsT(int stmtNum, int followingStmt);
};
// ai-gen end
