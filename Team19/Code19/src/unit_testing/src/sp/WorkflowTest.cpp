#include "sp/SPTokenizer/SPTokenizer.h"
#include "sp/SourceProcessor.h"
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

TEST_CASE("Test parser of SP on multipgole procedures", "[SourceProcessor]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";

	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	SourceProcessor sp(testFileName, pkbManager);

	REQUIRE_NOTHROW(sp.parseSIMPLE());
	REQUIRE_NOTHROW(sp.extractAndPopulate());

	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();

	auto variableReader = pkbReaderManager->getVariableReader();
	auto values1 = variableReader->getAllVariables();

	auto procedureReader = pkbReaderManager->getProcedureReader();
	auto values2 = procedureReader->getAllProcedures();

	auto statementReader = pkbReaderManager->getStatementReader();
	auto values3 = statementReader->getAllStatements();
	std::unordered_set<int> expectedValues3 = { 1 };
	REQUIRE(values3 == expectedValues3);

}


TEST_CASE("Test parser of SP on one procedures and multiple statements", "[SourceProcessor]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program4.txt";

	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	SourceProcessor sp(testFileName, pkbManager);

	REQUIRE_NOTHROW(sp.parseSIMPLE());
	REQUIRE_NOTHROW(sp.extractAndPopulate());

	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
	auto variableReader = pkbReaderManager->getVariableReader();
	auto values1 = variableReader->getAllVariables();

	auto procedureReader = pkbReaderManager->getProcedureReader();
	auto values2 = procedureReader->getAllProcedures();

	auto statementReader = pkbReaderManager->getStatementReader();
	auto values3 = statementReader->getAllStatements();
	std::unordered_set<int> expectedValues3 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	REQUIRE(values3 == expectedValues3);
}