#include "catch.hpp"

#include "pkb/PKBManager.h"

TEST_CASE("pkb/readers/patterns/WhilePatternReader") {
	auto pkbManager = std::make_shared<PKBManager>();
	auto pkbReaderManager = pkbManager->getPKBReaderManager();
	auto whilePatternReader = pkbReaderManager->getWhilePatternReader();
	auto pkbWriterManager = pkbManager->getPKBWriterManager();
	auto whilePatternWriter = pkbWriterManager->getWhilePatternWriter();

	SECTION("isEmpty") {
		REQUIRE(whilePatternReader->isEmpty());
	}

	whilePatternWriter->addWhileControlVariable(1, "x");
	whilePatternWriter->addWhileControlVariable(2, "y");
	whilePatternWriter->addWhileControlVariable(2, "z");
	whilePatternWriter->addWhileControlVariable(2, "x");
	SECTION("getControlVariable") {
		REQUIRE(whilePatternReader->getControlVariablesOfWhileStatement(1) == std::unordered_set<std::string>{"x"});
		REQUIRE(whilePatternReader->getControlVariablesOfWhileStatement(2) == std::unordered_set<std::string>{"x", "y", "z"});
	}

	SECTION("getStatementNumbersWithControlVariable") {
		REQUIRE(whilePatternReader->getStatementNumbersOfWhileControlVariable("x") == std::unordered_set<int>{1, 2});
		REQUIRE(whilePatternReader->getStatementNumbersOfWhileControlVariable("y") == std::unordered_set<int>{2});
	}
}