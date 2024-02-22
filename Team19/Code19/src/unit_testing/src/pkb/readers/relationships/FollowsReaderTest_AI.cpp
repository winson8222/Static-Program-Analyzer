#include "catch.hpp"
#include "pkb/PKBManager.h"
#include "pkb/stores/relationships/types/FollowsStore.h"

TEST_CASE("pkb/readers/relationships/FollowsReader") {
    auto followsStore = std::make_shared<FollowsStore>();
    FollowsReader followsReader(followsStore);

    SECTION("isEmpty: Empty on initialization") {
        REQUIRE(followsReader.isEmpty());
    }

    // Assume these methods exist to add follows relationships directly to the store for testing
    followsStore->addRelationship(1, 2);
    followsStore->addRelationship(2, 3);

    SECTION("isEmpty: Not empty after adding relationships") {
        REQUIRE_FALSE(followsReader.isEmpty());
    }

    SECTION("hasFollows") {
        REQUIRE(followsReader.hasFollows(1, 2));
        REQUIRE(followsReader.hasFollows(2, 3));
        REQUIRE_FALSE(followsReader.hasFollows(1, 3)); // Not directly follows
    }

    SECTION("getPreFollows") {
        auto preFollows = followsReader.getPreFollows(2);
        REQUIRE(preFollows == std::unordered_set<int>{1});
    }

    SECTION("getPostFollows") {
        auto postFollows = followsReader.getPostFollows(2);
        REQUIRE(postFollows == std::unordered_set<int>{3});
    }

    SECTION("getAllPreFollows") {
        auto allPreFollows = followsReader.getAllPreFollows();
        REQUIRE(allPreFollows.size() == 2);
        REQUIRE(allPreFollows.find(1) != allPreFollows.end());
        REQUIRE(allPreFollows.find(2) != allPreFollows.end());
    }

    SECTION("getAllPostFollows") {
        auto allPostFollows = followsReader.getAllPostFollows();
        REQUIRE(allPostFollows.size() == 2);
        REQUIRE(allPostFollows.find(2) != allPostFollows.end());
        REQUIRE(allPostFollows.find(3) != allPostFollows.end());
    }

}
