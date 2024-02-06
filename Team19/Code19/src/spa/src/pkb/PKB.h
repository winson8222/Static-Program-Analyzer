#pragma once

#include "pkb/stores/relationships/types/FollowsStore.h"
#include "pkb/stores/relationships/types/FollowsTStore.h"
#include "pkb/stores/relationships/types/UsesPStore.h"
#include "pkb/stores/relationships/types/UsesSStore.h"
#include "pkb/stores/relationships/types/ParentStore.h"
#include "pkb/stores/relationships/types/ParentTStore.h"

class PKB {
    public:
        PKB();
        FollowsStore followsStore;
        FollowsTStore followsTStore;

        ParentStore parentStore;
        ParentTStore parentTStore;

        UsesPStore usesPStore;
        UsesSStore usesSStore;
};