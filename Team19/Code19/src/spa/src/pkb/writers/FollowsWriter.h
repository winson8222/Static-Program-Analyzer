#pragma once

#include <memory>
#include "pkb/stores/relationships/types/FollowsStore.h"

class FollowsWriter {
private:
    std::shared_ptr<FollowsStore> followsStore;

public:
    explicit FollowsWriter(std::shared_ptr<FollowsStore> store): followsStore(std::move(store)) {}

    void addFollows(int precedingStmt, int followingStmt) {
        followsStore->addRelationship(precedingStmt, followingStmt);
    }

    void clear() {
        followsStore->clear();
    }
};
