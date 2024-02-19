#include "catch.hpp"
#include "pkb/PKBManager.h"
#include "pkb/stores/relationships/types/ParentTStore.h"

TEST_CASE("ParentTReader: Basic Functionality") {
    auto parentTStore = std::make_shared<ParentTStore>();
    ParentTReader parentTReader(parentTStore);

    SECTION("isEmpty on initialization") {
        REQUIRE(parentTReader.isEmpty());
    }

    SECTION("Adding and checking ParentT relationships") {
        // Direct parent-child relationships
        parentTStore->addRelationship(1, 2); // 1 is the parent of 2 directly
        parentTStore->addRelationship(2, 3); // 2 is the parent of 3 directly, making 1 an indirect parent of 3

        // Transitive parent-child relationships need to be explicitly added
        parentTStore->addRelationship(1, 3); // 1 is an indirect (transitive) parent of 3

        REQUIRE_FALSE(parentTReader.isEmpty());
        REQUIRE(parentTReader.hasParentT(1, 2)); // Direct relationship
        REQUIRE(parentTReader.hasParentT(1, 3)); // Transitive relationship
        REQUIRE(parentTReader.hasParentT(2, 3)); // Direct relationship
        REQUIRE_FALSE(parentTReader.hasParentT(2, 1)); // Incorrect direction

        auto parentTOf3 = parentTReader.getParentT(3);
        REQUIRE(parentTOf3.size() == 2); // Both 1 and 2 are parents of 3
        REQUIRE(parentTOf3.find(1) != parentTOf3.end());
        REQUIRE(parentTOf3.find(2) != parentTOf3.end());

        auto childTOf1 = parentTReader.getChildT(1);
        REQUIRE(childTOf1.size() == 2); // 2 and 3 are children of 1
        REQUIRE(childTOf1.find(2) != childTOf1.end());
        REQUIRE(childTOf1.find(3) != childTOf1.end());

        auto allParentTs = parentTReader.getAllParentTs();
        REQUIRE(allParentTs.size() == 2); // 1 and 2 are parents
        REQUIRE(allParentTs.find(1) != allParentTs.end());
        REQUIRE(allParentTs.find(2) != allParentTs.end());

        auto allChildrenT = parentTReader.getAllChildrenT();
        REQUIRE(allChildrenT.size() == 2); // 2 and 3 are children
        REQUIRE(allChildrenT.find(2) != allChildrenT.end());
        REQUIRE(allChildrenT.find(3) != allChildrenT.end());
    }

}
