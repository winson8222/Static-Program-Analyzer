#include "catch.hpp"
#include "pkb/stores/relationships/types/ParentStore.h"

// Tests the functionalities of ParentStore, focusing on parent-child relationships.
TEST_CASE("ParentStore Functionality") {
    ParentStore parentStore;

    // Tests adding relationships and checking their existence.
    SECTION("Add and Check Parent Relationships") {
        parentStore.addRelationship(1, 2);
        parentStore.addRelationship(1, 3);
        parentStore.addRelationship(2, 4);

        // Verifies that the relationships are correctly established.
        REQUIRE(parentStore.hasRelationship(1, 2));
        REQUIRE(parentStore.hasRelationship(1, 3));
        REQUIRE(parentStore.hasRelationship(2, 4));
        // Ensures that a non-existent relationship returns false.
        REQUIRE_FALSE(parentStore.hasRelationship(1, 4));
    }

        // Tests retrieving all direct parent-child relationships.
    SECTION("Retrieve Direct Parent-Child Relationships") {
        parentStore.addRelationship(1, 2);
        parentStore.addRelationship(1, 3);
        auto keyValueRelationships = parentStore.getKeyValueRelationships();

        // Expected map of parent to children relationships.
        auto expected = unordered_map<int, unordered_set<int>>{{1, {2, 3}}};
        REQUIRE(keyValueRelationships == expected);
    }

        // Tests the functionality of checking the empty state and clearing the store.
    SECTION("Check Empty State and Clear Functionality") {
        // Initially, the store should be empty.
        REQUIRE(parentStore.isEmpty());

        // Adding a relationship should change the store's state to non-empty.
        parentStore.addRelationship(1, 2);
        REQUIRE_FALSE(parentStore.isEmpty());

        // Clearing the store should reset its state to empty.
        parentStore.clear();
        REQUIRE(parentStore.isEmpty());
    }
}
