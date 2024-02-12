#pragma once

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/FollowsStore.h"
#include <memory>

class FollowsWriter : public IRelationshipWriter<int, int> {
private:
    std::shared_ptr<FollowsStore> followsStore;

public:
    explicit FollowsWriter(std::shared_ptr<FollowsStore> store) : followsStore(std::move(store)) {}

    void addRelationship(int precedingStmt, int followingStmt) override {
        followsStore->addKeyValue(precedingStmt, followingStmt);
    }

    void clear() {
        followsStore->clear();
    }
};
