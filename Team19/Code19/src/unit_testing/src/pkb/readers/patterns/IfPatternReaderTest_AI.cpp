#include "catch.hpp"

#include "pkb/PKBManager.h"

TEST_CASE("pkb/readers/patterns/IfPatternReader") {
	auto pkbManager = std::make_shared<PKBManager>();
	auto pkbReaderManager = pkbManager->getPKBReaderManager();
	auto ifPatternReader = pkbReaderManager->getIfPatternReader();
	auto pkbWriterManager = pkbManager->getPKBWriterManager();
	auto ifPatternWriter = pkbWriterManager->getIfPatternWriter();

	SECTION("isEmpty") {
		REQUIRE(ifPatternReader->isEmpty());
	}

	ifPatternWriter->addIfControlVariable(1, "x");
	ifPatternWriter->addIfControlVariable(2, "y");
	ifPatternWriter->addIfControlVariable(2, "z");
	ifPatternWriter->addIfControlVariable(2, "x");
	SECTION("getControlVariable") {
		REQUIRE(ifPatternReader->getControlVariablesOfIfStatement(1) == std::unordered_set<std::string>{"x"});
		REQUIRE(ifPatternReader->getControlVariablesOfIfStatement(2) == std::unordered_set<std::string>{"x", "y", "z"});
	}

	SECTION("getStatementNumbersWithControlVariable") {
		REQUIRE(ifPatternReader->getStatementNumbersOfIfControlVariable("x") == std::unordered_set<int>{1, 2});
		REQUIRE(ifPatternReader->getStatementNumbersOfIfControlVariable("y") == std::unordered_set<int>{2});
	}
}