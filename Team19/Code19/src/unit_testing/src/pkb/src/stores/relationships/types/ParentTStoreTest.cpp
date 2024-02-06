#include "catch.hpp"
#include "pkb/stores/relationships/types/ParentTStore.h"

// Tests the functionalities of ParentTStore, focusing on transitive parent-child relationships.
TEST_CASE("ParentTStore Functionality") {
    ParentTStore parentTStore;

    // Tests adding and checking transitive relationships.
    SECTION("Add and Check Transitive Parent Relationships") {
        parentTStore.addRelationship(1, 2);
        parentTStore.addRelationship(2, 3);
        parentTStore.addRelationship(1, 3); // Demonstrates transitivity (1->2->3 implies 1->3).

        // Verifies direct and transitive relationships.
        REQUIRE(parentTStore.hasRelationship(1, 2));
        REQUIRE(parentTStore.hasRelationship(1, 3));
        REQUIRE(parentTStore.hasRelationship(2, 3));
        // Confirms that inverse or non-existent relationships are correctly identified.
        REQUIRE_FALSE(parentTStore.hasRelationship(2, 1));
    }

        // Tests retrieving transitive parent-child relationships.
    SECTION("Retrieve Transitive Parent-Child Relationships") {
        parentTStore.addRelationship(1, 2);
        parentTStore.addRelationship(2, 3);
        parentTStore.addRelationship(1, 3); // Explicitly tests transitivity.

        // Expected structure reflecting both direct and transitive relationships.
        auto keyValueRelationships = parentTStore.getKeyValueRelationships();
        auto expected = unordered_map<int, unordered_set<int>>{{1, {2, 3}}, {2, {3}}};
        REQUIRE(keyValueRelationships == expected);
    }

        // Tests the functionality of clearing the store and checking its empty state.
    SECTION("Check Empty State and Clear Functionality") {
        // Store should be empty initially.
        REQUIRE(parentTStore.isEmpty());

        // Adding relationships changes the state to non-empty.
        parentTStore.addRelationship(1, 2);
        REQUIRE_FALSE(parentTStore.isEmpty());

        // Clearing all relationships should return the store to an empty state.
        parentTStore.clear();
        REQUIRE(parentTStore.isEmpty());
    }
}
