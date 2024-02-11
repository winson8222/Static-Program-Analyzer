#pragma once

#include <memory>
#include "pkb/stores/relationships/types/FollowsTStore.h"

class FollowsTWriter {
private:
    std::shared_ptr<FollowsTStore> followsTStore;

public:
    explicit FollowsTWriter(std::shared_ptr<FollowsTStore> store): followsTStore(std::move(store)) {}

    void addFollowsT(int precedingStmt, int followingStmt) {
        followsTStore->addRelationship(precedingStmt, followingStmt);
    }

    void clear() {
        followsTStore->clear();
    }
};
