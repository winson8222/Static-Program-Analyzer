#include "catch.hpp"
#include "pkb/stores/relationships/types/FollowsTStore.h"

using namespace std;

/**
 * Unit tests for the FollowsTStore class.
 *
 * The FollowsTStore class manages transitive 'Follows*' relationships within a SIMPLE program,
 * meaning it tracks not only direct 'Follows' relationships but also indirect ones where
 * a statement follows another through one or more intermediate statements.
 * These tests ensure that the FollowsTStore correctly records and queries these transitive relationships.
 */
TEST_CASE("pkb/stores/FollowsTStore") {

    // Test case for retrieving transitive Follows relationships
    SECTION("getFollowsT") {
        // Initialize FollowsTStore and add relationships
        FollowsTStore followsTStore;
        followsTStore.addRelationship(1, 2); // Statement 1 followed by Statement 2
        followsTStore.addRelationship(1, 3); // Statement 1 indirectly followed by Statement 3 (transitively)
        followsTStore.addRelationship(2, 3); // Statement 2 followed by Statement 3

        // Expected relationships mapping, including both direct and indirect relationships
        auto expected = unordered_map<int, unordered_set<int>>{
                {1, {2, 3}}, // Statement 1 is followed by both Statement 2 and 3
                {2, {3}}     // Statement 2 is followed by Statement 3
        };

        // Verify that stored relationships match the expected mapping
        REQUIRE(followsTStore.getKeyValueRelationships() == expected);
    }

        // Test case for checking the existence of transitive Follows relationships
    SECTION("isFollowsT") {
        // Initialize FollowsTStore and add relationships
        FollowsTStore followsTStore;
        followsTStore.addRelationship(1, 2); // Statement 1 followed by Statement 2
        followsTStore.addRelationship(1, 3); // Statement 1 indirectly followed by Statement 3 (transitively)
        followsTStore.addRelationship(2, 3); // Statement 2 followed by Statement 3

        // Verify the existence of specified Follows relationships
        REQUIRE(followsTStore.hasRelationship(1, 3)); // Transitive relationship exists
        REQUIRE(followsTStore.hasRelationship(2, 3)); // Direct relationship exists

        // Verify that non-existent relationships return false
        REQUIRE_FALSE(followsTStore.hasRelationship(1, 4)); // Relationship does not exist
        REQUIRE_FALSE(followsTStore.hasRelationship(2, 1)); // Inverse relationship does not exist
    }

        // Test case for retrieving the predecessors in transitive Follows relationships
    SECTION("getPreFollowsT") {
        // Initialize FollowsTStore and add relationships
        FollowsTStore followsTStore;
        followsTStore.addRelationship(1, 2);
        followsTStore.addRelationship(1, 3);
        followsTStore.addRelationship(2, 3);

        // Verify that correct predecessors are returned for each statement
        auto expected = unordered_set<int>{1}; // Statement 1 precedes Statement 2
        REQUIRE(followsTStore.getRelationshipsByValue(2) == expected);
        expected = unordered_set<int>{1, 2}; // Statements 1 and 2 precede Statement 3
        REQUIRE(followsTStore.getRelationshipsByValue(3) == expected);

        // Verify that querying for non-existent relationships returns the correct result
        REQUIRE_FALSE(followsTStore.getRelationshipsByValue(1).size() > 0); // No statement precedes Statement 1
    }

        // Test case for retrieving the successors in transitive Follows relationships
    SECTION("getPostFollowsT") {
        // Initialize FollowsTStore and add relationships
        FollowsTStore followsTStore;
        followsTStore.addRelationship(1, 2);
        followsTStore.addRelationship(1, 3);
        followsTStore.addRelationship(2, 3);

        // Verify that correct successors are returned for each statement
        auto expected = unordered_set<int>{2, 3}; // Statements 2 and 3 follow Statement 1
        REQUIRE(followsTStore.getRelationshipsByKey(1) == expected);
        expected = unordered_set<int>{3}; // Statement 3 follows Statement 2
        REQUIRE(followsTStore.getRelationshipsByKey(2) == expected);
    }
}
