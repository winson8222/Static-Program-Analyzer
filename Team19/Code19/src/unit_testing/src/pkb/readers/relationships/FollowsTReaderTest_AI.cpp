#include "catch.hpp"
#include "pkb/PKBManager.h"
#include "pkb/stores/relationships/types/FollowsTStore.h"
#include "pkb/readers/relationships/FollowsTReader.h"

TEST_CASE("pkb/readers/relationships/FollowsTReader") {
    auto followsTStore = std::make_shared<FollowsTStore>();
    FollowsTReader followsTReader(followsTStore);

    SECTION("isEmpty on initialization") {
        REQUIRE(followsTReader.isEmpty());
    }

    // Simulate the scenario where transitive relationships are discovered and need to be explicitly added
    followsTStore->addRelationship(1, 2);
    followsTStore->addRelationship(2, 3);
    followsTStore->addRelationship(1, 3); // Explicitly adding transitive relationship
    followsTStore->addRelationship(3, 4);
    followsTStore->addRelationship(1, 4); // Adding because of transitive closure from 1 through 3 to 4
    followsTStore->addRelationship(2, 4); // Adding because of transitive closure from 2 through 3 to 4
    SECTION("isEmpty: Not empty after adding relationships") {
        REQUIRE_FALSE(followsTReader.isEmpty());
    }

    SECTION("hasFollowsT") {
      REQUIRE(followsTReader.hasFollowsT(1, 2));
      REQUIRE(followsTReader.hasFollowsT(2, 3));
      REQUIRE(followsTReader.hasFollowsT(1, 3)); // Checking direct transitive relationship
      REQUIRE(followsTReader.hasFollowsT(3, 4));
      REQUIRE(followsTReader.hasFollowsT(1, 4)); // Checking extended transitive relationship
      REQUIRE(followsTReader.hasFollowsT(2, 4)); // Additional transitive relationship

    }

    SECTION("getPreFollowsT") {
        auto preFollowsT_4 = followsTReader.getPreFollowsT(4);
        REQUIRE(preFollowsT_4 == std::unordered_set<int>{1, 2, 3}); // 1, 2, and 3 are all predecessors of 4 in FollowsT
    }

    SECTION("getPostFollowsT") {
        auto postFollowsT_1 = followsTReader.getPostFollowsT(1);
        REQUIRE(postFollowsT_1 == std::unordered_set<int>{2, 3, 4}); // 1 is a predecessor of 2, 3, and 4 in FollowsT
    }

    SECTION("getAllPreFollowsT") {
        auto allPreFollowsT = followsTReader.getAllPreFollowsT();
        REQUIRE(allPreFollowsT.size() == 3); // 1, 2, 3 are all valid predecessors in some FollowsT relationships
        REQUIRE(allPreFollowsT == std::unordered_set<int>{1, 2, 3});
    }

    SECTION("getAllPostFollowsT") {
        auto allPostFollowsT = followsTReader.getAllPostFollowsT();
        REQUIRE(allPostFollowsT.size() == 3); // 2, 3, 4 are all valid successors in some FollowsT relationships
        REQUIRE(allPostFollowsT == std::unordered_set<int>{2, 3, 4});
    }
}
