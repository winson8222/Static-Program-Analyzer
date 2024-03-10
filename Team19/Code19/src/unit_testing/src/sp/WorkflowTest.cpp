#include "sp/SPTokenizer/SPTokenizer.h"
#include "sp/SourceProcessor.h"
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

TEST_CASE("Test parser of SP on multipgole procedures", "[SourceProcessor]") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure main {\n"
                                "\tread helloWorld;\n"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	SourceProcessor sp(filename, pkbManager);

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
    std::filesystem::remove(filename);
}


TEST_CASE("Test parser of SP on one procedures and multiple statements", "[SourceProcessor]") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure procedure {\n"
                                "\twhile (!(read > procedure)) {\n"
                                "\t\tif = if;\n"
                                "\t} \n"
                                "\n"
                                "\tif (then < 2) then {\n"
                                "\t\telse = else;\n"
                                "\t} else {\n"
                                "\t\twhile = then;\n"
                                "\t}\n"
                                "\n"
                                "\tread = 1 + program;\n"
                                "\n"
                                "\tcall call;\n"
                                "\tprint read;\n"
                                "\tread print;\n"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));

	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	SourceProcessor sp(filename, pkbManager);

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
    std::filesystem::remove(filename);
}