#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: AssignPattern") {
	SECTION("Basic AssignPattern") {
		std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();

		std::string filename = "./sample.txt";
		std::string sampleProgram = "procedure proc1 {"
			"   read x;"
			"   while (y > 1) {"
			"       y = y + 1; }" // 3
			"   read x;"
			"   while (y > 5) {"
			"       z = z + 1; }}" // 6
			"procedure proc2 {"
			"   read x;"
			"   while (y > 1) {"
			"       y = y + 1; }" // 9
			"   read x; }";
		std::ofstream file;
		file.open(filename);
		file << sampleProgram;
		file.close();

		REQUIRE(std::filesystem::exists(filename));
		SourceProcessor sp = SourceProcessor(filename, pkbManager);
		std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
		std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
		assignPatternWriter->clear();

		sp.parseSIMPLE();
		sp.extractAndPopulate();
		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();

		std::shared_ptr<AssignPatternReader> assignPatternReader = pkbReaderManager->getAssignPatternReader();
		std::unordered_set<int> expectedAssignPattern = { 3, 6, 9 };
		REQUIRE(assignPatternReader->getAllStatementNumbers() == expectedAssignPattern);
		REQUIRE(assignPatternReader->getLHS(3) == "y");
		REQUIRE(assignPatternReader->getLHS(6) == "z");
		REQUIRE(assignPatternReader->getLHS(9) == "y");
		REQUIRE(assignPatternReader->getRHS(3) == "'y''1''+'");
		REQUIRE(assignPatternReader->getRHS(6) == "'z''1''+'");
		REQUIRE(assignPatternReader->getRHS(9) == "'y''1''+'");

		REQUIRE(assignPatternReader->getStatementNumbersWithLHS("y") == std::unordered_set<int>({ 3, 9 }));
		REQUIRE(assignPatternReader->getStatementNumbersWithLHS("z") == std::unordered_set<int>({ 6 }));
		REQUIRE(assignPatternReader->getStatementNumbersWithPartialRHS("y") == std::unordered_set<int>({ 3, 9 }));
		REQUIRE(assignPatternReader->getStatementNumbersWithPartialRHS("z") == std::unordered_set<int>({ 6 }));
		REQUIRE(assignPatternReader->getStatementNumbersWithPartialRHS("1") == std::unordered_set<int>({ 3, 6, 9 }));
		std::filesystem::remove(filename);
	}
}

TEST_CASE("sp/SourceProcessor: Complicated Reverse-Polish Notation") {
	SECTION("Basic AssignPattern") {
		std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();

		std::string filename = "./sample.txt";
		std::string sampleProgram = "procedure proc1 {"
			"  x = (3 + 2) * 8 - 4 / 8 + (3 - 2) % x; }";
		std::ofstream file;
		file.open(filename);
		file << sampleProgram;
		file.close();

		REQUIRE(std::filesystem::exists(filename));
		SourceProcessor sp = SourceProcessor(filename, pkbManager);
		std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
		std::shared_ptr<AssignPatternWriter> assignPatternWriter = pkbWriterManager->getAssignPatternWriter();
		assignPatternWriter->clear();

		sp.parseSIMPLE();
		sp.extractAndPopulate();
		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();

		std::shared_ptr<AssignPatternReader> assignPatternReader = pkbReaderManager->getAssignPatternReader();
		std::unordered_set<int> expectedAssignPattern = { 1 };
		REQUIRE(assignPatternReader->getAllStatementNumbers() == expectedAssignPattern);
		REQUIRE(assignPatternReader->getLHS(1) == "x");
		REQUIRE(assignPatternReader->getRHS(1) == "'3''2''+''8''*''4''8''/''-''3''2''-''x''%''+'");

		REQUIRE(assignPatternReader->getStatementNumbersWithLHS("x") == std::unordered_set<int>({ 1 }));
        std::unordered_set<int> test = assignPatternReader->getStatementNumbersWithPartialRHS("'3'");
		std::filesystem::remove(filename);
	}
}