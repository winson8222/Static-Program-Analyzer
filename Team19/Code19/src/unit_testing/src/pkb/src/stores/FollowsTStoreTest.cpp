#include "catch.hpp"
#include "pkb/stores/FollowsTStore.h"

using namespace std;

TEST_CASE("PKB FollowsTStore") {
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
}