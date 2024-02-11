#include "catch.hpp"
#include "pkb/stores/relationships/types/ParentStore.h"

/**
 * Unit tests for the ParentStore class within the Program Knowledge Base (PKB).
 *
 * The ParentStore manages parent-child relationships within a SIMPLE program, specifically focusing on
 * which statements (parent) directly contain other statements (child) within their scope.
 * These tests aim to verify the functionality of adding, querying, and managing these relationships.
 */
TEST_CASE("ParentStore Functionality") {

    // Initializes an instance of ParentStore for testing.
    ParentStore parentStore;

    // Tests the ability to add parent-child relationships and verify their existence.
    SECTION("Add and Check Parent Relationships") {
        // Adds parent-child relationships.
        parentStore.addRelationship(1, 2); // Statement 1 is the parent of Statement 2.
        parentStore.addRelationship(1, 3); // Statement 1 is also the parent of Statement 3.
        parentStore.addRelationship(2, 4); // Statement 2 is the parent of Statement 4.

        // Checks if the added relationships are correctly identified.
        REQUIRE(parentStore.hasRelationship(1, 2)); // Verifies parent-child relationship.
        REQUIRE(parentStore.hasRelationship(1, 3)); // Verifies another parent-child relationship.
        REQUIRE(parentStore.hasRelationship(2, 4)); // Verifies a third parent-child relationship.

        // Verifies that a non-existent relationship is correctly identified as false.
        REQUIRE_FALSE(parentStore.hasRelationship(1, 4)); // Statement 1 is not directly the parent of Statement 4.
    }

        // Tests retrieving all direct parent-child relationships stored.
    SECTION("Retrieve Direct Parent-Child Relationships") {
        // Adds parent-child relationships.
        parentStore.addRelationship(1, 2);
        parentStore.addRelationship(1, 3);

        // Retrieves the mapping of parent statements to their direct children.
        auto keyValueRelationships = parentStore.getKeyValueRelationships();

        // Defines the expected mapping of parent to child(ren) for validation.
        auto expected = std::unordered_map<int, std::unordered_set<int>>{{1, {2, 3}}}; // Statement 1 has children Statements 2 and 3.

        // Compares the retrieved relationships against the expected mapping.
        REQUIRE(keyValueRelationships == expected);
    }

        // Tests the functionality of checking the empty state of the store and its ability to clear all relationships.
    SECTION("Check Empty State and Clear Functionality") {
        // Verifies that the store is initially empty.
        REQUIRE(parentStore.isEmpty());

        // After adding a relationship, the store should no longer be empty.
        parentStore.addRelationship(1, 2); // Adds a single parent-child relationship.
        REQUIRE_FALSE(parentStore.isEmpty()); // The store should now contain relationships.

        // Clears all relationships from the store.
        parentStore.clear();

        // Verifies that the store is empty after the clear operation.
        REQUIRE(parentStore.isEmpty());
    }
}
