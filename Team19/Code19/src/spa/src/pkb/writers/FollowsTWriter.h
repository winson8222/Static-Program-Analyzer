#pragma once

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/FollowsTStore.h"
#include <memory>

class FollowsTWriter : public IRelationshipWriter<int, int> {
private:
    std::shared_ptr<FollowsTStore> followsTStore;

public:
    explicit FollowsTWriter(std::shared_ptr<FollowsTStore> store) : followsTStore(std::move(store)) {}

    void addRelationship(int precedingStmt, int followingStmt) override {
        followsTStore->addKeyValue(precedingStmt, followingStmt);
    }

    void clear() {
        followsTStore->clear();
    }
};
