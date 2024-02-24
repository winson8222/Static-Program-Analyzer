#include "catch.hpp"
#include <memory>
#include "pkb/PKBManager.h"

TEST_CASE("qps/QueryProcessingSubsystem: FollowsReader") {
    auto pkbManager = std::make_shared<PKBManager>();
    auto followsWriter = pkbManager->getPKBWriterManager()->getFollowsWriter();

    // Prepare the environment: Clear the store before populating it to ensure a clean state.
    followsWriter->clear();

    // Populating Follows relationships for retrieval tests.
    followsWriter->addFollows(1, 2); // Statement 1 follows statement 2
    followsWriter->addFollows(2, 3); // Statement 2 follows statement 3
    followsWriter->addFollows(4, 5); // Statement 4 follows statement 5

    auto followsReader = pkbManager->getPKBReaderManager()->getFollowsReader();

    SECTION("Verify retrieval of all Preceding and Following statements") {
        REQUIRE(followsReader->getAllPreFollows() == std::unordered_set<int>{1, 2, 4});
        REQUIRE(followsReader->getAllPostFollows() == std::unordered_set<int>{2, 3, 5});
    }

    SECTION("Check specific Follows relationships exist") {
        REQUIRE(followsReader->hasFollows(1, 2) == true);
        REQUIRE(followsReader->hasFollows(2, 3) == true);
        REQUIRE(followsReader->hasFollows(1, 3) == false); // There's no direct Follows relationship between 1 and 3
    }

    SECTION("Retrieve statements that directly follow a given statement") {
        auto postFollows1 = followsReader->getPostFollows(1);
        auto postFollows2 = followsReader->getPostFollows(2);
        REQUIRE(postFollows1.find(2) != postFollows1.end());
        REQUIRE(postFollows2.find(3) != postFollows2.end());
    }

    SECTION("Retrieve statements that are directly preceded by a given statement") {
        auto preFollows3 = followsReader->getPreFollows(3);
        auto preFollows5 = followsReader->getPreFollows(5);
        REQUIRE(preFollows3.find(2) != preFollows3.end());
        REQUIRE(preFollows5.find(4) != preFollows5.end());
    }

    SECTION("Check if FollowsStore is empty after clearing") {
        followsWriter->clear();
        REQUIRE(followsReader->isEmpty() == true);
    }

}
