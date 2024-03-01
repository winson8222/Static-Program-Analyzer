#include "catch.hpp"

#include "commons/ShuntingYard.h"
#include "pkb/PKBManager.h"

TEST_CASE("pkb/readers/patterns/AssignPatternReader") {
	auto pkbManager = std::make_shared<PKBManager>();
	auto pkbReaderManager = pkbManager->getPKBReaderManager();
	auto assignPatternReader = pkbReaderManager->getAssignPatternReader();
	auto pkbWriterManager = pkbManager->getPKBWriterManager();
	auto assignPatternWriter = pkbWriterManager->getAssignPatternWriter();

	SECTION("isEmpty") {
		REQUIRE(assignPatternReader->isEmpty());
	}

	assignPatternWriter->addAssignPattern(1, "x", ShuntingYard::convertToPostfix("1"));
	assignPatternWriter->addAssignPattern(2, "y", ShuntingYard::convertToPostfix("x + 2"));
	assignPatternWriter->addAssignPattern(3, "z", ShuntingYard::convertToPostfix("x + y * 5 + 4"));

	SECTION("getLHS") {
		REQUIRE(assignPatternReader->getLHS(1) == "x");
		REQUIRE(assignPatternReader->getLHS(2) == "y");
	}

	SECTION("getStatementNumbersWithLHS") {
		REQUIRE(assignPatternReader->getStatementNumbersWithLHS("x") == std::unordered_set<int>{1});
		REQUIRE(assignPatternReader->getStatementNumbersWithLHS("y") == std::unordered_set<int>{2});
	}

	SECTION("getRHS") {
		REQUIRE(assignPatternReader->getRHS(1) == ShuntingYard::convertToPostfix("1"));
		REQUIRE(assignPatternReader->getRHS(2) == ShuntingYard::convertToPostfix("x + 2"));
	}

	SECTION("getStatementNumbersWithRHS") {
		REQUIRE(assignPatternReader->getStatementNumbersWithRHS(ShuntingYard::convertToPostfix("1")) == std::unordered_set<int>{1});
		REQUIRE(assignPatternReader->getStatementNumbersWithRHS(ShuntingYard::convertToPostfix("x + 2")) == std::unordered_set<int>{2});
	}

	SECTION("getStatementNumberWithPartialRHS") {
		REQUIRE(assignPatternReader->getStatementNumbersWithPartialRHS(ShuntingYard::convertToPostfix("x")) == std::unordered_set<int>{2, 3});
		REQUIRE(assignPatternReader->getStatementNumbersWithPartialRHS("y") == std::unordered_set<int>{3});
		REQUIRE(assignPatternReader->getStatementNumbersWithPartialRHS(ShuntingYard::convertToPostfix("y * 5")) == std::unordered_set<int>{3});
		REQUIRE(assignPatternReader->getStatementNumbersWithPartialRHS(ShuntingYard::convertToPostfix("5 + 4")).empty());
		REQUIRE(assignPatternReader->getStatementNumbersWithPartialRHS("5") == std::unordered_set<int>{3});
	}

	SECTION("getStatementNumberWithLHSPartialRHS") {
		REQUIRE(assignPatternReader->getStatementNumbersWithLHSPartialRHS("x", ShuntingYard::convertToPostfix("1")) == std::unordered_set<int>{1});
		REQUIRE(assignPatternReader->getStatementNumbersWithLHSPartialRHS("y", ShuntingYard::convertToPostfix("2")) == std::unordered_set<int>{2});
		REQUIRE(assignPatternReader->getStatementNumbersWithLHSPartialRHS("z", ShuntingYard::convertToPostfix("y * 5")) == std::unordered_set<int>{3});
		REQUIRE(assignPatternReader->getStatementNumbersWithLHSPartialRHS("z", ShuntingYard::convertToPostfix("5 + 4")).empty());
		REQUIRE(assignPatternReader->getStatementNumbersWithLHSPartialRHS("z", "5") == std::unordered_set<int>{3});
	}

}