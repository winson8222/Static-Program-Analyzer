#include "catch.hpp"

#include "pkb/PKBManager.h"

TEST_CASE("pkb/readers/relationships/NextReader") {
	auto pkbManager = std::make_shared<PKBManager>();
	auto nextReader = pkbManager->getPKBReaderManager()->getNextReader();
	auto nextWriter = pkbManager->getPKBWriterManager()->getNextWriter();

	SECTION("isEmpty on initialization") {
		REQUIRE(nextReader->isEmpty());
	}

	nextWriter->addRelationship(1, 2); // 1 is the next of 2
	nextWriter->addRelationship(1, 3); // 1 is also the next of 3

	SECTION("isEmpty: Not empty after adding relationships") {
		REQUIRE_FALSE(nextReader->isEmpty());
	}

	SECTION("hasNext") {
		REQUIRE(nextReader->hasNext(1, 2));
		REQUIRE(nextReader->hasNext(1, 3));
		REQUIRE_FALSE(nextReader->hasNext(2, 1)); // Incorrect direction
	}

	SECTION("getNext") {
		auto nextOf1 = nextReader->getNext(1);
		REQUIRE(nextOf1.size() == 2);
		REQUIRE(nextOf1.find(2) != nextOf1.end());
		REQUIRE(nextOf1.find(3) != nextOf1.end());
	}

	SECTION("getPrevious") {
		auto previousOf2 = nextReader->getPrevious(2);
		REQUIRE(previousOf2.size() == 1);
		REQUIRE(previousOf2.find(1) != previousOf2.end());
	}

	SECTION("getAllNext") {
		auto allNext = nextReader->getAllNext();
		REQUIRE(allNext.size() == 2); // Correctly reflects two unique nexts
		REQUIRE(allNext.find(2) != allNext.end());
		REQUIRE(allNext.find(3) != allNext.end());
	}

	SECTION("getAllPrevious") {
		auto allPrevious = nextReader->getAllPrevious();
		REQUIRE(allPrevious.size() == 1); // Correctly reflects one unique previous
		REQUIRE(allPrevious.find(1) != allPrevious.end());
	}

	SECTION("getNext: No Relationships Exist") {
		REQUIRE(nextReader->getNext(99).empty());
	}

	SECTION("getPrevious: No Relationships Exist") {
		REQUIRE(nextReader->getPrevious(99).empty());
	}

	nextWriter->clear();
	// Example of adding complex next relationships
	nextWriter->addRelationship(1, 2);
	nextWriter->addRelationship(1, 3);
	nextWriter->addRelationship(2, 4);
	nextWriter->addRelationship(3, 5);
	nextWriter->addRelationship(3, 6);
	nextWriter->addRelationship(4, 7);
}
