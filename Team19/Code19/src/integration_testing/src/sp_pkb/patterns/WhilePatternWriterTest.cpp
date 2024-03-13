#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: WhilePattern") {
	SECTION("Basic WhilePattern") {
		std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();

		std::string filename = "./sample.txt";
		std::string sampleProgram = "procedure proc1 {"
			"   while (y > 1) {"	// 1
			"       y = y + 1; }"
			"   read x;"
			"   while ((y > 5) && (z == y)) {"	// 4
			"       z = z + 1; }}"
			"procedure proc2 {"
			"   read x;"
			"   while (y > 1) {"	// 7
			"		while (k != y) {"	// 8
			"			while (!(!(h <= k - h))) {"	// 9
			"			y = y + 1; }}}"
			"   read x; }";
		std::ofstream file;
		file.open(filename);
		file << sampleProgram;
		file.close();

		REQUIRE(std::filesystem::exists(filename));
		SourceProcessor sp = SourceProcessor(filename, pkbManager);
		std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
		std::shared_ptr<WhilePatternWriter> whilePatternWriter = pkbWriterManager->getWhilePatternWriter();

		sp.parseSIMPLE();
		sp.extractAndPopulate();

		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
		std::shared_ptr<WhilePatternReader> whilePatternReader = pkbReaderManager->getWhilePatternReader();

		std::unordered_set<int> expectedWhilePattern1 = { 1, 4, 7, 8, 9 };
		REQUIRE(whilePatternReader->getAllStatementNumbers() == expectedWhilePattern1);

		std::unordered_set<int> expectedWhilePattern2 = { 1, 4, 7, 8 };
		REQUIRE(whilePatternReader->getStatementNumbersOfWhileControlVariable("y") == expectedWhilePattern2);

		std::unordered_set<int> expectedWhilePattern3 = { 9 };
		REQUIRE(whilePatternReader->getStatementNumbersOfWhileControlVariable("h") == expectedWhilePattern3);

		std::unordered_set<std::string> expectedWhilePattern4 = { "y", "z", "k", "h" };
		REQUIRE(whilePatternReader->getAllControlPatterns() == expectedWhilePattern4);

		std::unordered_set<std::string> expectedWhilePattern5 = { "k", "h" };
		REQUIRE(whilePatternReader->getControlPatternsWithStatementNumber(9) == expectedWhilePattern5);

		std::unordered_set<std::string> expectedWhilePattern6 = { "y", "z" };
		REQUIRE(whilePatternReader->getControlPatternsWithStatementNumber(4) == expectedWhilePattern6);

		std::filesystem::remove(filename);
	}

}