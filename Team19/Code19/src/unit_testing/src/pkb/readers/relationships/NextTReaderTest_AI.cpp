#include "catch.hpp"
#include <iostream>

#include "pkb/PKBManager.h"
TEST_CASE("pkb/readers/relationships/NextTReader") {
	auto pkbManager = std::make_shared<PKBManager>();
	auto nextWriter = pkbManager->getPKBWriterManager()->getNextWriter();
	auto nextTReader = pkbManager->getPKBReaderManager()->getNextTReader();

	SECTION("getNextT: Empty") {
		REQUIRE(nextTReader->getNextT(1).empty());
	}

	SECTION("getNextT: Non-empty") {
		nextWriter->addNext(1, 2);
		nextWriter->addNext(2, 3);
		REQUIRE(nextTReader->getNextT(1) == std::unordered_set<int>{2, 3});
		REQUIRE(nextTReader->getNextT(2) == std::unordered_set<int>{3});
	}

	SECTION("hasNextT: True") {
		nextWriter->addNext(1, 2);
		REQUIRE(nextTReader->hasNextT(1, 2));
	}

	SECTION("hasNextT: False") {
		REQUIRE_FALSE(nextTReader->hasNextT(1, 2));
	}

	SECTION("getPreviousT: Empty") {
		REQUIRE(nextTReader->getPreviousT(1).empty());
	}

	SECTION("getPreviousT: Non-empty") {
		nextWriter->addNext(1, 2);
		nextWriter->addNext(2, 3);
		nextWriter->addNext(3, 2);
		nextWriter->addNext(3, 4);
		REQUIRE(nextTReader->getPreviousT(1).empty());
		REQUIRE(nextTReader->getPreviousT(2) == std::unordered_set<int>{1, 3});
		REQUIRE(nextTReader->getPreviousT(3) == std::unordered_set<int>{1, 2});
		REQUIRE(nextTReader->getPreviousT(4) == std::unordered_set<int>{1, 2, 3});
	}

	SECTION("getAllPreviousT: Empty") {
		REQUIRE(nextTReader->getAllPreviousT().empty());
	}

	SECTION("getAllPreviousT: Non-empty") {
		nextWriter->addNext(1, 2);
		nextWriter->addNext(2, 3);
		nextWriter->addNext(3, 2);
		nextWriter->addNext(3, 4);
		std::unordered_set<int> expected = {1, 2, 3};
		REQUIRE(nextTReader->getAllPreviousT() == expected);
	}

	SECTION("getAllNextT: Empty") {
		REQUIRE(nextTReader->getAllNextT().empty());
	}

	SECTION("getAllNextT: Non-empty") {
		nextWriter->addNext(1, 2);
		nextWriter->addNext(2, 3);
		nextWriter->addNext(3, 2);
		nextWriter->addNext(3, 4);
		std::unordered_set<int> expected = {2, 3, 4};
		REQUIRE(nextTReader->getAllNextT() == expected);
	}

	SECTION("getAllNextTRelationships: Empty") {
		REQUIRE(nextTReader->getAllNextTRelationships().empty());
	}

	SECTION("getAllNextTRelationships: Non-empty") {
		nextWriter->addNext(1, 2);
		nextWriter->addNext(2, 3);
		nextWriter->addNext(3, 2);
		nextWriter->addNext(3, 4);
		std::unordered_map<int, std::unordered_set<int>> expected = {
			{1, {2, 3, 4}},
			{2, {3, 4}},
			{3, {2, 4}}
		};
		REQUIRE(nextTReader->getAllNextTRelationships() == expected);
	}

	SECTION("getAllReversedNextTRelationships: Empty") {
		REQUIRE(nextTReader->getAllReversedNextTRelationships().empty());
	}

	SECTION("getAllReversedNextTRelationships: Non-empty") {
		nextWriter->addNext(1, 2);
		nextWriter->addNext(2, 3);
		nextWriter->addNext(3, 2);
		nextWriter->addNext(3, 4);
		std::unordered_map<int, std::unordered_set<int>> expected = {
			{2, {1, 3}},
			{3, {1, 2}},
			{4, {1, 2, 3}}
		};
		REQUIRE(nextTReader->getAllReversedNextTRelationships() == expected);
	}
}
