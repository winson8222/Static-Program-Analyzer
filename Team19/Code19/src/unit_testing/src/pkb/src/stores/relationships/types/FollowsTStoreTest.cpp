#include "catch.hpp"
#include "pkb/stores/relationships/types/FollowsTStore.h"

using namespace std;

TEST_CASE("pkb/stores/FollowsTStore") {
    SECTION("getFollowsT") {
        FollowsTStore followsTStore;
        followsTStore.addRelationship(1, 2);
        followsTStore.addRelationship(1, 3);
        followsTStore.addRelationship(2, 3);
        auto expected = unordered_map<int, unordered_set<int>>{
                {1, {2, 3}},
                {2, {3}}
        };
        REQUIRE(followsTStore.getKeyValueRelationships() == expected);
    }

    SECTION("isFollowsT") {
        FollowsTStore followsTStore;
        followsTStore.addRelationship(1, 2);
        followsTStore.addRelationship(1, 3);
        followsTStore.addRelationship(2, 3);
        REQUIRE(followsTStore.hasRelationship(1, 3));
        REQUIRE(followsTStore.hasRelationship(2, 3));
        REQUIRE_FALSE(followsTStore.hasRelationship(1, 4));
        REQUIRE_FALSE(followsTStore.hasRelationship(2, 1));
    }

    SECTION("getPreFollowsT") {
        FollowsTStore followsTStore;
        followsTStore.addRelationship(1, 2);
        followsTStore.addRelationship(1, 3);
        followsTStore.addRelationship(2, 3);
        auto expected = unordered_set<int>{1};
        REQUIRE(followsTStore.getRelationshipsByValue(2) == expected);
        expected = unordered_set<int>{1, 2};
        REQUIRE(followsTStore.getRelationshipsByValue(3) == expected);
        expected = unordered_set<int>{2};
        REQUIRE_FALSE(followsTStore.getRelationshipsByValue(3) == expected);
        REQUIRE_FALSE(followsTStore.getRelationshipsByValue(1).size() > 0);
    }

    SECTION("getPostFollowsT") {
        FollowsTStore followsTStore;
        followsTStore.addRelationship(1, 2);
        followsTStore.addRelationship(1, 3);
        followsTStore.addRelationship(2, 3);
        auto expected = unordered_set<int>{2, 3};
        REQUIRE(followsTStore.getRelationshipsByKey(1) == expected);
        expected = unordered_set<int>{3};
        REQUIRE(followsTStore.getRelationshipsByKey(2) == expected);
    }
}