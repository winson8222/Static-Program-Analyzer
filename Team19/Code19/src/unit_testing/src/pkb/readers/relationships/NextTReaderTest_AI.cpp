#include "catch.hpp"

#include "pkb/PKBManager.h"
TEST_CASE("pkb/readers/relationships/NextTReader") {
	auto pkbManager = std::make_shared<PKBManager>();
	auto nextWriter = pkbManager->getPKBWriterManager()->getNextWriter();
	auto nextTReader = pkbManager->getPKBReaderManager()->getNextTReader();
	auto pkbCacheManager = pkbManager->getPKBCacheManager();

	SECTION("getAllPreviousT: Empty") {
		REQUIRE(nextTReader->getAllPreviousT().empty());
	}

	SECTION("getNextT: Empty") {
		REQUIRE(nextTReader->getNextT(1).empty());
	}

	SECTION("getAllNextT: Empty") {
		REQUIRE(nextTReader->getAllNextT().empty());
	}

	SECTION("getAllNextTRelationships: Empty") {
		REQUIRE(nextTReader->getAllNextTRelationships().empty());
	}

	SECTION("getAllReversedNextTRelationships: Empty") {
		REQUIRE(nextTReader->getAllReversedNextTRelationships().empty());
	}

	nextWriter->addNext(1, 2);
	nextWriter->addNext(2, 3);
	nextWriter->addNext(3, 2);
	nextWriter->addNext(3, 4);

	pkbCacheManager->populateCache();

	SECTION("getNextT: Non-empty") {
		REQUIRE(nextTReader->getNextT(1) == std::unordered_set<int>{2, 3, 4});
		REQUIRE(nextTReader->getNextT(2) == std::unordered_set<int>{3, 4});
		REQUIRE(nextTReader->getNextT(3) == std::unordered_set<int>{2, 4});
	}

	SECTION("hasNextT: True") {
		REQUIRE(nextTReader->hasNextT(1, 2));
	}

	SECTION("hasNextT: False") {
		REQUIRE_FALSE(nextTReader->hasNextT(2, 1));
	}

	SECTION("getPreviousT: Empty") {
		REQUIRE(nextTReader->getPreviousT(1).empty());
	}

	SECTION("getPreviousT: Non-empty") {
		REQUIRE(nextTReader->getPreviousT(1).empty());
		REQUIRE(nextTReader->getPreviousT(2) == std::unordered_set<int>{1, 3});
		REQUIRE(nextTReader->getPreviousT(3) == std::unordered_set<int>{1, 2});
		REQUIRE(nextTReader->getPreviousT(4) == std::unordered_set<int>{1, 2, 3});
	}

	SECTION("getAllPreviousT: Non-empty") {
		std::unordered_set<int> expected = {1, 2, 3};
		REQUIRE(nextTReader->getAllPreviousT() == expected);
	}

	SECTION("getAllNextT: Non-empty") {
		std::unordered_set<int> expected = {2, 3, 4};
		REQUIRE(nextTReader->getAllNextT() == expected);
	}



	SECTION("getAllNextTRelationships: Non-empty") {
		std::unordered_map<int, std::unordered_set<int>> expected = {
			{1, {2, 3, 4}},
			{2, {3, 4}},
			{3, {2, 4}}
		};
		REQUIRE(nextTReader->getAllNextTRelationships() == expected);
	}

	SECTION("getAllReversedNextTRelationships: Non-empty") {
		std::unordered_map<int, std::unordered_set<int>> expected = {
			{2, {1, 3}},
			{3, {1, 2}},
			{4, {1, 2, 3}}
		};
		REQUIRE(nextTReader->getAllReversedNextTRelationships() == expected);
	}

	SECTION("getNextT") {
		REQUIRE(nextTReader->getNextT(1) == std::unordered_set<int>{2, 3, 4});
		REQUIRE(nextTReader->getNextT(2) == std::unordered_set<int>{3, 4});
		REQUIRE(nextTReader->getNextT(3) == std::unordered_set<int>{2, 4});
		REQUIRE(nextTReader->getNextT(4).empty());
	}
}
