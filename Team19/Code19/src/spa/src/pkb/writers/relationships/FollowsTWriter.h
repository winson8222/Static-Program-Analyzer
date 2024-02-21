#pragma once

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/FollowsTStore.h"
#include <memory>

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class FollowsTWriter : public IRelationshipWriter<int, int> {
private:
    std::shared_ptr<FollowsTStore> followsTStore;

public:
    explicit FollowsTWriter(std::shared_ptr<FollowsTStore> store) : followsTStore(std::move(store)) {}

    void addRelationship(int precedingStmt, int followingStmt) override {
      addFollowsT(precedingStmt, followingStmt);
    }

    void clear() override {
      followsTStore->clear();
    }

    // Custom methods
    /**
     * @brief Adds a "FollowsT" relationship between a preceding statement and a following statement.
     * @param stmtNum The statement number of the preceding statement.
     * @param followingStmt The statement number of the following statement.
     */
    void addFollowsT(int stmtNum, int followingStmt) {
      followsTStore->addRelationship(stmtNum, followingStmt);
    }
};
// ai-gen end
