#include "catch.hpp"
#include "pkb/stores/relationships/types/ParentTStore.h"

/**
 * Unit tests for the ParentTStore class within the Program Knowledge Base (PKB).
 *
 * The ParentTStore manages transitive parent-child relationships within a SIMPLE program,
 * specifically focusing on statements (parents) that contain other statements (children)
 * either directly or through one or more levels of nesting. These tests aim to verify the
 * functionality of adding, querying, and managing these transitive relationships.
 */
TEST_CASE("ParentTStore Functionality") {
    // Initializes an instance of ParentTStore for testing.
    ParentTStore parentTStore;

    // Tests adding transitive parent-child relationships and verifying their existence.
    SECTION("Add and Check Transitive Parent Relationships") {
        // Adds parent-child relationships demonstrating transitivity.
        parentTStore.addRelationship(1, 2); // Statement 1 is the parent of Statement 2.
        parentTStore.addRelationship(2, 3); // Statement 2 is the parent of Statement 3, implying 1 is a transitive parent of 3.
        parentTStore.addRelationship(1, 3); // Directly adding the transitive relationship for testing.

        // Verifies direct and transitive relationships.
        REQUIRE(parentTStore.hasRelationship(1, 2)); // Direct parent-child relationship.
        REQUIRE(parentTStore.hasRelationship(1, 3)); // Transitive parent-child relationship.
        REQUIRE(parentTStore.hasRelationship(2, 3)); // Direct parent-child relationship.

        // Ensures that inverse or non-existent relationships are correctly identified as false.
        REQUIRE_FALSE(parentTStore.hasRelationship(2, 1)); // Inverse relationship does not exist.
    }

        // Tests retrieving all stored transitive parent-child relationships.
    SECTION("Retrieve Transitive Parent-Child Relationships") {
        // Adds relationships to test transitivity.
        parentTStore.addRelationship(1, 2);
        parentTStore.addRelationship(2, 3);
        parentTStore.addRelationship(1, 3); // Explicitly adding transitive relationship.

        // Retrieves the mapping of parent statements to their direct and indirect children.
        auto keyValueRelationships = parentTStore.getKeyValueRelationships();

        // Defines the expected mapping of parent to child(ren) including transitivity.
        auto expected = unordered_map<int, unordered_set<int>>{
                {1, {2, 3}}, // Statement 1 has children Statements 2 and 3 (transitive).
                {2, {3}}     // Statement 2 has child Statement 3 (direct).
        };

        // Compares the retrieved relationships against the expected mapping.
        REQUIRE(keyValueRelationships == expected);
    }

        // Tests the store's ability to clear all relationships and check its empty state.
    SECTION("Check Empty State and Clear Functionality") {
        // Verifies the store is initially empty.
        REQUIRE(parentTStore.isEmpty());

        // Adding a relationship makes the store non-empty.
        parentTStore.addRelationship(1, 2); // Adds a single parent-child relationship.
        REQUIRE_FALSE(parentTStore.isEmpty()); // The store should now contain relationships.

        // Clears all relationships from the store, returning it to an empty state.
        parentTStore.clear();
        REQUIRE(parentTStore.isEmpty()); // The store should be empty after clearing.
    }
}
