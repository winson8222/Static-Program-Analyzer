#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: FollowsTReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto followsTWriter = pkbManager->getPKBWriterManager()->getFollowsTWriter();

    // Preparing the environment: Clearing the store before populating it to ensure a clean state.
    followsTWriter->clear();

    // Populating FollowsT relationships for retrieval tests.
    followsTWriter->addRelationship(1, 2);
    followsTWriter->addRelationship(1, 3); // Transitive relationship example
    followsTWriter->addRelationship(2, 3);

    auto followsTReader = pkbManager->getPKBReaderManager()->getFollowsTReader();

    SECTION("Verify retrieval of all transitive Follows relationships") {
        REQUIRE(followsTReader->hasFollowsT(1, 2) == true);
        REQUIRE(followsTReader->hasFollowsT(1, 3) == true);
        REQUIRE(followsTReader->hasFollowsT(2, 3) == true);
    }

    SECTION("Check specific transitive Follows relationship exists") {
        REQUIRE(followsTReader->hasFollowsT(1, 3) == true); // Directly added and through transitivity
        REQUIRE(followsTReader->hasFollowsT(999, 1000) == false); // Test for non-existent statements
    }

    SECTION("Retrieve all preceding and following statement numbers in transitive Follows relationships") {
        auto allPreceding = followsTReader->getAllPreFollowsT();
        auto allFollowing = followsTReader->getAllPostFollowsT();
        REQUIRE(allPreceding.size() > 0);
        REQUIRE(allFollowing.size() > 0);
    }

    SECTION("Retrieve specific statements that precede or follow in transitive Follows relationships") {
        auto preFollowsT = followsTReader->getPreFollowsT(3);
        auto postFollowsT = followsTReader->getPostFollowsT(1);
        REQUIRE(preFollowsT.find(1) != preFollowsT.end());
        REQUIRE(preFollowsT.find(2) != preFollowsT.end());
        REQUIRE(postFollowsT.find(2) != postFollowsT.end());
        REQUIRE(postFollowsT.find(3) != postFollowsT.end());
    }

    SECTION("Check if FollowsTStore is empty after clearing") {
        followsTWriter->clear();
        REQUIRE(followsTReader->isEmpty() == true);
    }

}
