#include "PKB.h"

PKB::PKB() {
    // Initialize all relationships
    followsTStore = FollowsTStore();
    followsStore = FollowsStore();
    parentTStore = ParentTStore();
    parentStore = ParentStore();
    usesPStore = UsesPStore();
    usesSStore = UsesSStore();

    // Initialize all entities

};
