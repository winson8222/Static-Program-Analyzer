#include "catch.hpp"
#include "pkb/stores/relationships/types/FollowsStore.h"

using namespace std;

/**
 * Unit tests for the FollowsStore class.
 *
 * The FollowsStore class manages direct 'Follows' relationships where one statement
 * directly follows another in a SIMPLE program. These tests ensure that the
 * FollowsStore correctly records and queries these relationships.
 */
TEST_CASE("pkb/stores/FollowsStore") {

    // Test case for retrieving direct Follows relationships
    SECTION("getFollows") {
        // Initialize FollowsStore and add relationships
        FollowsStore followsStore;
        followsStore.addRelationship(1, 2); // Statement 1 follows Statement 2
        followsStore.addRelationship(2, 3); // Statement 2 follows Statement 3

        // Expected relationships mapping
        auto expected = unordered_map<int, unordered_set<int>>{
                {1, {2}}, // Statement 1 is followed by Statement 2
                {2, {3}}  // Statement 2 is followed by Statement 3
        };

        // Verify that stored relationships match the expected mapping
        REQUIRE(followsStore.getKeyValueRelationships() == expected);
    }

        // Test case for checking the existence of direct Follows relationships
    SECTION("isFollows") {
        // Initialize FollowsStore and add relationships
        FollowsStore followsStore;
        followsStore.addRelationship(1, 2); // Statement 1 follows Statement 2
        followsStore.addRelationship(2, 3); // Statement 2 follows Statement 3

        // Verify the existence of specified Follows relationships
        REQUIRE(followsStore.hasRelationship(1, 2));
        REQUIRE(followsStore.hasRelationship(2, 3));

        // Verify that non-existent and non-transitive relationships return false
        REQUIRE_FALSE(followsStore.hasRelationship(1, 3)); // Not transitive
        REQUIRE_FALSE(followsStore.hasRelationship(2, 1)); // Inverse relationship
    }

        // Test case for retrieving the predecessors in Follows relationships
    SECTION("getPreFollows") {
        // Initialize FollowsStore and add relationships
        FollowsStore followsStore;
        followsStore.addRelationship(1, 2); // Statement 1 follows Statement 2
        followsStore.addRelationship(2, 3); // Statement 2 follows Statement 3

        // Verify that the correct predecessor is returned for each statement
        auto expected = unordered_set<int>{1};
        REQUIRE(followsStore.getRelationshipsByValue(2) == expected); // Statement 1 precedes Statement 2
        expected = unordered_set<int>{2};
        REQUIRE(followsStore.getRelationshipsByValue(3) == expected); // Statement 2 precedes Statement 3

        // Verify that querying a statement with no predecessors returns an empty set
        REQUIRE(followsStore.getRelationshipsByValue(1).empty());
    }

      // Test case for retrieving the successors in Follows relationships
    SECTION("getPostFollows") {
        // Initialize FollowsStore and add relationships
        FollowsStore followsStore;
        followsStore.addRelationship(1, 2); // Statement 1 follows Statement 2
        followsStore.addRelationship(2, 3); // Statement 2 follows Statement 3

        // Verify that the correct successor is returned for each statement
        auto expected = unordered_set<int>{2};
        REQUIRE(followsStore.getRelationshipsByKey(1) == expected); // Statement 2 follows Statement 1
        expected = unordered_set<int>{3};
        REQUIRE(followsStore.getRelationshipsByKey(2) == expected); // Statement 3 follows Statement 2
    }
}
