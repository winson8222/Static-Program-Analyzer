#include "catch.hpp"
#include "pkb/stores/relationships/types/ParentStore.h"
#include "pkb/readers/relationships/ParentReader.h"

TEST_CASE("ParentReader: Basic Functionality") {
    auto parentStore = std::make_shared<ParentStore>();
    ParentReader parentReader(parentStore);

    SECTION("isEmpty on initialization") {
        REQUIRE(parentReader.isEmpty());
    }

    SECTION("Adding and checking Parent relationships") {
        parentStore->addRelationship(1, 2); // 1 is the parent of 2
        parentStore->addRelationship(1, 3); // 1 is also the parent of 3

        REQUIRE_FALSE(parentReader.isEmpty());
        REQUIRE(parentReader.hasParent(1, 2));
        REQUIRE(parentReader.hasParent(1, 3));
        REQUIRE_FALSE(parentReader.hasParent(2, 1)); // Incorrect direction

        auto parentsOf2 = parentReader.getParent(2);
        REQUIRE(parentsOf2.size() == 1);
        REQUIRE(parentsOf2.find(1) != parentsOf2.end());

        auto childrenOf1 = parentReader.getChild(1);
        REQUIRE(childrenOf1.size() == 2);
        REQUIRE(childrenOf1.find(2) != childrenOf1.end());
        REQUIRE(childrenOf1.find(3) != childrenOf1.end());

        auto allChildren = parentReader.getAllChildren();
        REQUIRE(allChildren.size() == 2); // Correctly reflects two unique children
        REQUIRE(allChildren.find(2) != allChildren.end());
        REQUIRE(allChildren.find(3) != allChildren.end());
    }
}


TEST_CASE("ParentReader: No Relationships Exist") {
    auto parentStore = std::make_shared<ParentStore>();
    ParentReader parentReader(parentStore);

    // Assuming relationships are added in other tests, ensure clean state
    parentStore->clear(); // Ensure the store is empty for this test

    SECTION("Querying for non-existent parent or child returns empty") {
        REQUIRE(parentReader.getParent(99).empty());
        REQUIRE(parentReader.getChild(99).empty());
    }
}

TEST_CASE("ParentReader: Complex Relationship Scenarios") {
    auto parentStore = std::make_shared<ParentStore>();
    ParentReader parentReader(parentStore);

    // Example of adding complex parent-child relationships
    parentStore->addRelationship(1, 2);
    parentStore->addRelationship(1, 3);
    parentStore->addRelationship(2, 4);
    parentStore->addRelationship(3, 5);
    parentStore->addRelationship(3, 6);

    SECTION("Retrieving all parents and children") {
        auto allParents = parentReader.getAllParents();
        auto allChildren = parentReader.getAllChildren();

        REQUIRE(allParents.size() == 3); // Parents: 1, 2, and 3
        REQUIRE(allParents.find(1) != allParents.end());
        REQUIRE(allParents.find(2) != allParents.end());
        REQUIRE(allParents.find(3) != allParents.end());

        REQUIRE(allChildren.size() == 5); // Children: 2, 3, 4, 5, and 6
        REQUIRE(allChildren.find(2) != allChildren.end());
        REQUIRE(allChildren.find(3) != allChildren.end());
        REQUIRE(allChildren.find(4) != allChildren.end());
        REQUIRE(allChildren.find(5) != allChildren.end());
        REQUIRE(allChildren.find(6) != allChildren.end());
    }

    SECTION("Querying complex relationships") {
        // Test for getting children of a parent with multiple children
        auto childrenOf1 = parentReader.getChild(1);
        REQUIRE(childrenOf1.size() == 2); // Direct children of 1 are 2 and 3
        REQUIRE(childrenOf1.find(2) != childrenOf1.end());
        REQUIRE(childrenOf1.find(3) != childrenOf1.end());

        // Test for getting parent of a child that is a second-level descendant
        auto parentOf4 = parentReader.getParent(4);
        REQUIRE(parentOf4.size() == 2); // Parent of 4 is 2
        REQUIRE(parentOf4.find(2) != parentOf4.end());
    }
}
