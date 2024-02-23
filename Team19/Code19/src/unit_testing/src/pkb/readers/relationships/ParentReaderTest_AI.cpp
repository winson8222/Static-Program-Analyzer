#include "catch.hpp"
#include "pkb/stores/relationships/types/ParentStore.h"
#include "pkb/readers/relationships/ParentReader.h"

TEST_CASE("pkb/readers/relationships/ParentReader") {
    auto parentStore = std::make_shared<ParentStore>();
    ParentReader parentReader(parentStore);

    SECTION("isEmpty on initialization") {
        REQUIRE(parentReader.isEmpty());
    }

    parentStore->addRelationship(1, 2); // 1 is the parent of 2
    parentStore->addRelationship(1, 3); // 1 is also the parent of 3


    SECTION("isEmpty: Not empty after adding relationships") {
        REQUIRE_FALSE(parentReader.isEmpty());
    }

    SECTION("hasParent") {
        REQUIRE(parentReader.hasParent(1, 2));
        REQUIRE(parentReader.hasParent(1, 3));
        REQUIRE_FALSE(parentReader.hasParent(2, 1)); // Incorrect direction
    }

    SECTION("getParent") {
        auto parentsOf2 = parentReader.getParent(2);
        REQUIRE(parentsOf2.size() == 1);
        REQUIRE(parentsOf2.find(1) != parentsOf2.end());
    }

    SECTION("getChild") {
        auto childrenOf1 = parentReader.getChild(1);
        REQUIRE(childrenOf1.size() == 2);
        REQUIRE(childrenOf1.find(2) != childrenOf1.end());
        REQUIRE(childrenOf1.find(3) != childrenOf1.end());
    }

    SECTION("getAllChildren") {
        auto allChildren = parentReader.getAllChildren();
        REQUIRE(allChildren.size() == 2); // Correctly reflects two unique children
        REQUIRE(allChildren.find(2) != allChildren.end());
        REQUIRE(allChildren.find(3) != allChildren.end());
    }
    SECTION("getParent: No Relationships Exist") {
      REQUIRE(parentReader.getParent(99).empty());
    }

    SECTION("getChild: No Relationships Exist") {
        REQUIRE(parentReader.getChild(99).empty());
    }

    parentStore->clear();
    // Example of adding complex parent-child relationships
    parentStore->addRelationship(1, 2);
    parentStore->addRelationship(1, 3);
    parentStore->addRelationship(2, 4);
    parentStore->addRelationship(3, 5);
    parentStore->addRelationship(3, 6);

    SECTION("getAllParents: Complex Relationships") {
      auto allParents = parentReader.getAllParents();
      REQUIRE(allParents.size() == 3); // Parents: 1, 2, and 3
      REQUIRE(allParents.find(1) != allParents.end());
      REQUIRE(allParents.find(2) != allParents.end());
      REQUIRE(allParents.find(3) != allParents.end());
    }

    SECTION("getAllChildren: Complex Relationships") {
      auto allChildren = parentReader.getAllChildren();
      REQUIRE(allChildren.size() == 5); // Children: 2, 3, 4, 5, and 6
      REQUIRE(allChildren.find(2) != allChildren.end());
      REQUIRE(allChildren.find(3) != allChildren.end());
      REQUIRE(allChildren.find(4) != allChildren.end());
      REQUIRE(allChildren.find(5) != allChildren.end());
      REQUIRE(allChildren.find(6) != allChildren.end());
    }

    SECTION("getChild: Complex Relationships") {
      // Test for getting children of a parent with multiple children
      auto childrenOf1 = parentReader.getChild(1);
      REQUIRE(childrenOf1.size() == 2); // Direct children of 1 are 2 and 3
      REQUIRE(childrenOf1.find(2) != childrenOf1.end());
      REQUIRE(childrenOf1.find(3) != childrenOf1.end());
    }
    SECTION("getParent: Complex Relationships") {
      // Test for getting parent of a child that is a second-level descendant
      auto parentOf4 = parentReader.getParent(4);
      REQUIRE(parentOf4.size() == 1); // Parent of 4 is 2
      REQUIRE(parentOf4.find(2) != parentOf4.end());
    }
}


