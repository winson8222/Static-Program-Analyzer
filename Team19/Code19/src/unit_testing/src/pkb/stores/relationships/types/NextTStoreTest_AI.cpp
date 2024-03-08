/*
#include "catch.hpp"

#include "pkb/stores/relationships/types/NextStore.h"
#include "pkb/stores/relationships/types/NextTStore.h"

TEST_CASE("pkb/stores/relationships/types/NextTStore") {
	// This whole test suite will run 10 times, and fail on the 10th time in the below line.
	auto nextStore = std::make_shared<NextStore>();
	auto nextTStore = std::make_shared<NextTStore>(nextStore);
	nextStore->addRelationship(1, 2);
	nextStore->addRelationship(2, 3);
	nextStore->addRelationship(3, 4);
	SECTION("populateAndGetPreviousT") {
		REQUIRE(nextTStore->populateAndGetPreviousT(4, std::unordered_set<int>{}) == std::unordered_set<int>{3, 2, 1});
		REQUIRE(nextTStore->getRelationshipsByValue(3) == std::unordered_set<int>{2, 1});
		REQUIRE(nextTStore->getRelationshipsByValue(2) == std::unordered_set<int>{1});
		REQUIRE(nextTStore->getRelationshipsByValue(1).empty());
	}
	nextStore->addRelationship(3, 2);
	SECTION("populateAndGetPreviousT: Loop") {
		REQUIRE(nextTStore->populateAndGetPreviousT(4, std::unordered_set<int>{}) == std::unordered_set<int>{3, 2, 1});
		REQUIRE(nextTStore->getRelationshipsByValue(3) == std::unordered_set<int>{1, 2});
		REQUIRE(nextTStore->getRelationshipsByValue(2) == std::unordered_set<int>{1, 3});
		REQUIRE(nextTStore->getRelationshipsByValue(1).empty());
		REQUIRE(nextTStore->getRelationshipsByKey(4).empty());
		REQUIRE(nextTStore->getRelationshipsByKey(3) == std::unordered_set<int>{2, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(2) == std::unordered_set<int>{3, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(1) == std::unordered_set<int>{2, 3, 4});
	}

	SECTION("populateAndGetNextT") {
		REQUIRE(nextTStore->populateAndGetNextT(1, std::unordered_set<int>{}) == std::unordered_set<int>{2, 3, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(2) == std::unordered_set<int>{3, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(3) == std::unordered_set<int>{2, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(4).empty());
	}

	SECTION("populateAndGetNext: Partial Population") {
		REQUIRE(nextTStore->populateAndGetNextT(2, std::unordered_set<int>{}) == std::unordered_set<int>{3, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(1).empty());
		REQUIRE(nextTStore->getRelationshipsByKey(2) == std::unordered_set<int>{3, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(3) == std::unordered_set<int>{2, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(4).empty());
	}

	SECTION("populateAndGetAllPreviousT") {
		REQUIRE(nextTStore->populateAndGetAllPreviousT() == std::unordered_set<int>{1, 2, 3});
		REQUIRE(nextTStore->getRelationshipsByValue(1).empty());
		REQUIRE(nextTStore->getRelationshipsByValue(2) == std::unordered_set<int>{1, 3});
		REQUIRE(nextTStore->getRelationshipsByValue(3) == std::unordered_set<int>{1, 2});
		REQUIRE(nextTStore->getRelationshipsByValue(4) == std::unordered_set<int>{1, 2, 3});
		REQUIRE(nextTStore->hasPreviousTPopulated(2));
		REQUIRE(nextTStore->hasPreviousTPopulated(3));
		REQUIRE(nextTStore->hasPreviousTPopulated(4));
	}

	SECTION("populateAndGetAllNextT") {
		REQUIRE(nextTStore->populateAndGetAllNextT() == std::unordered_set<int>{2, 3, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(1) == std::unordered_set<int>{2, 3, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(2) == std::unordered_set<int>{3, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(3) == std::unordered_set<int>{2, 4});
		REQUIRE(nextTStore->getRelationshipsByKey(4).empty());
		REQUIRE_FALSE(nextTStore->hasPreviousTPopulated(1));
		REQUIRE_FALSE(nextTStore->hasPreviousTPopulated(2));
		REQUIRE_FALSE(nextTStore->hasPreviousTPopulated(3));
		REQUIRE_FALSE(nextTStore->hasPreviousTPopulated(4));
		REQUIRE(nextTStore->hasNextTPopulated(1));
		REQUIRE(nextTStore->hasNextTPopulated(2));
		REQUIRE(nextTStore->hasNextTPopulated(3));
	}

	SECTION("populateAndGetEntireNextTStore: Not Reversed") {
		REQUIRE(nextTStore->populateAndGetEntireNextTStore(false) == std::unordered_map<int, std::unordered_set<int>>{
			{1, std::unordered_set<int>{2, 3, 4}},
			{2, std::unordered_set<int>{3, 4}},
			{3, std::unordered_set<int>{2, 4}}});
		REQUIRE(nextTStore->hasPreviousTPopulated(2));
		REQUIRE(nextTStore->hasPreviousTPopulated(3));
		REQUIRE(nextTStore->hasPreviousTPopulated(4));
		REQUIRE(nextTStore->hasNextTPopulated(1));
		REQUIRE(nextTStore->hasNextTPopulated(2));
		REQUIRE(nextTStore->hasNextTPopulated(3));
		REQUIRE(nextTStore->getRelationshipsByKey(4).empty());
		REQUIRE(nextTStore->getRelationshipsByValue(1).empty());
	}

	SECTION("populateAndGetEntireNextTStore: Reversed") {
		REQUIRE(nextTStore->populateAndGetEntireNextTStore(true) == std::unordered_map<int, std::unordered_set<int>> {
			{2, std::unordered_set<int>{1, 3}},
			{3, std::unordered_set<int>{1, 2}},
			{4, std::unordered_set<int>{1, 2, 3}}});
		REQUIRE(nextTStore->hasPreviousTPopulated(2));
		REQUIRE(nextTStore->hasPreviousTPopulated(3));
		REQUIRE(nextTStore->hasPreviousTPopulated(4));
		REQUIRE(nextTStore->hasNextTPopulated(1));
		REQUIRE(nextTStore->hasNextTPopulated(2));
		REQUIRE(nextTStore->hasNextTPopulated(3));
		REQUIRE(nextTStore->getRelationshipsByKey(4).empty());
		REQUIRE(nextTStore->getRelationshipsByValue(1).empty());
	}

	SECTION("populateNextTStore") {
		REQUIRE(nextTStore->populateNextTStore());
		REQUIRE(nextTStore->hasPreviousTPopulated(2));
		REQUIRE(nextTStore->hasPreviousTPopulated(3));
		REQUIRE(nextTStore->hasPreviousTPopulated(4));
		REQUIRE(nextTStore->hasNextTPopulated(1));
		REQUIRE(nextTStore->hasNextTPopulated(2));
		REQUIRE(nextTStore->hasNextTPopulated(3));
		REQUIRE(nextTStore->getRelationshipsByKey(4).empty());
		REQUIRE(nextTStore->getRelationshipsByValue(1).empty());
		REQUIRE(nextTStore->populateAndGetEntireNextTStore(false) == std::unordered_map<int, std::unordered_set<int>>{
			{1, std::unordered_set<int>{2, 3, 4}},
			{2, std::unordered_set<int>{3, 4}},
			{3, std::unordered_set<int>{2, 4}}});
	}

	SECTION("getNextT") {
		nextTStore->populateNextTStore();
		REQUIRE(nextTStore->getNextT(1) == std::unordered_set<int>{2, 3, 4});
		REQUIRE(nextTStore->getNextT(2) == std::unordered_set<int>{3, 4});
		REQUIRE(nextTStore->getNextT(3) == std::unordered_set<int>{2, 4});
		REQUIRE(nextTStore->getNextT(4).empty());
	}

	SECTION("getPreviousT") {
		nextTStore->populateNextTStore();
		REQUIRE(nextTStore->getPreviousT(1).empty());
		REQUIRE(nextTStore->getPreviousT(2) == std::unordered_set<int>{1, 3});
		REQUIRE(nextTStore->getPreviousT(3) == std::unordered_set<int>{1, 2});
		REQUIRE(nextTStore->getPreviousT(4) == std::unordered_set<int>{1, 2, 3});
	}

	SECTION("getAllPreviousT") {
		nextTStore->populateNextTStore();
		REQUIRE(nextTStore->getAllPreviousT() == std::unordered_set<int>{1, 2, 3});
	}

	SECTION("getAllNextT") {
		nextTStore->populateNextTStore();
		REQUIRE(nextTStore->getAllNextT() == std::unordered_set<int>{2, 3, 4});
	}

	SECTION("clear") {
		nextTStore->addRelationship(1, 2);
		nextTStore->populateNextT(1);
		nextTStore->populatePreviousT(4);
		REQUIRE_FALSE(nextTStore->getRelationshipsByKey(1).empty());
		REQUIRE_FALSE(nextTStore->getRelationshipsByValue(2).empty());
		REQUIRE(nextTStore->hasNextTPopulated(1));
		REQUIRE(nextTStore->hasPreviousTPopulated(4));
		nextTStore->clear();
		REQUIRE(nextTStore->getRelationshipsByKey(1).empty());
		REQUIRE(nextTStore->getRelationshipsByValue(2).empty());
		REQUIRE_FALSE(nextTStore->hasNextTPopulated(1));
		REQUIRE_FALSE(nextTStore->hasPreviousTPopulated(4));
	}
}
*/
