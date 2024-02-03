#include "catch.hpp"
#include "pkb/stores/FollowsTStore.h"

using namespace std;

TEST_CASE("pkb/stores/FollowsTStore") {
    SECTION("getFollowsT") {
        FollowsTStore followsTStore;
        followsTStore.addFollowsT(1, 2);
        followsTStore.addFollowsT(1, 3);
        followsTStore.addFollowsT(2, 3);
        auto expected = unordered_map<int, unordered_set<int>>{
                {1, {2, 3}},
                {2, {3}}
        };
        REQUIRE(followsTStore.getFollowsT() == expected);
    }

    SECTION("isFollowsT") {
        FollowsTStore followsTStore;
        followsTStore.addFollowsT(1, 2);
        followsTStore.addFollowsT(1, 3);
        followsTStore.addFollowsT(2, 3);
        REQUIRE(followsTStore.isFollowsT(1, 2));
        REQUIRE(followsTStore.isFollowsT(1, 3));
        REQUIRE(followsTStore.isFollowsT(2, 3));
        REQUIRE_FALSE(followsTStore.isFollowsT(1, 4));
        REQUIRE_FALSE(followsTStore.isFollowsT(2, 1));
    }

    SECTION("getPreFollowsT") {
        FollowsTStore followsTStore;
        followsTStore.addFollowsT(1, 2);
        followsTStore.addFollowsT(1, 3);
        followsTStore.addFollowsT(2, 3);
        auto expected = unordered_set<int>{1};
        REQUIRE(followsTStore.getPreFollowsT(2) == expected);
        expected = unordered_set<int>{1, 2};
        REQUIRE(followsTStore.getPreFollowsT(3) == expected);
        expected = unordered_set<int>{2};
        REQUIRE_FALSE(followsTStore.getPreFollowsT(3) == expected);
        REQUIRE_FALSE(followsTStore.getPreFollowsT(1).size() > 0);
    }

    SECTION("getPostFollowsT") {
        FollowsTStore followsTStore;
        followsTStore.addFollowsT(1, 2);
        followsTStore.addFollowsT(1, 3);
        followsTStore.addFollowsT(2, 3);
        auto expected = unordered_set<int>{2, 3};
        REQUIRE(followsTStore.getPostFollowsT(1) == expected);
        expected = unordered_set<int>{3};
        REQUIRE(followsTStore.getPostFollowsT(2) == expected);
    }
}