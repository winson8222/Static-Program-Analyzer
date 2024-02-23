#include "catch.hpp"
#include "pkb/PKBManager.h"
#include "pkb/stores/relationships/types/ParentTStore.h"
#include "pkb/readers/relationships/ParentTReader.h"

TEST_CASE("ParentTReader: Basic Functionality", "[ParentTReader]") {
    auto parentTStore = std::make_shared<ParentTStore>();
    ParentTReader parentTReader(parentTStore);

    SECTION("isEmpty on initialization") {
        REQUIRE(parentTReader.isEmpty());
    }

    parentTStore->addRelationship(1, 2);
    parentTStore->addRelationship(2, 3);
    parentTStore->addRelationship(1, 3); // Explicitly adding transitive relationship for testing

    SECTION("isEmpty: Not empty after adding relationships") {
      REQUIRE_FALSE(parentTReader.isEmpty());
    }

    SECTION("hasParentT") {
        REQUIRE(parentTReader.hasParentT(1, 2));
        REQUIRE(parentTReader.hasParentT(1, 3));
        REQUIRE(parentTReader.hasParentT(2, 3));
        REQUIRE_FALSE(parentTReader.hasParentT(3, 1)); // Incorrect direction, should not exist
    }

    SECTION("getParentT") {
      // Test retrieval of transitive parents and children
      auto parentTOf3 = parentTReader.getParentT(3);
      REQUIRE(parentTOf3.size() == 2); // 1 and 2 are transitive parents of 3
      REQUIRE(parentTOf3.count(1));
      REQUIRE(parentTOf3.count(2));
    }

    SECTION("getChildT") {
        auto childTOf1 = parentTReader.getChildT(1);
        REQUIRE(childTOf1.size() == 2); // 2 and 3 are transitive children of 1
        REQUIRE(childTOf1.count(2));
        REQUIRE(childTOf1.count(3));
    }

}