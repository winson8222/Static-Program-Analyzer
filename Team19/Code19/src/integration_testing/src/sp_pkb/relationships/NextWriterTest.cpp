#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Next") {
	SECTION("Next Extractions") {
		std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
		std::string filename = "sample.txt";
		std::string sampleProgram = "procedure proc1 {"
									"   read x;\n" // 1
									"	print y;\n"	// 2
									"	x = y + z;\n"		// 3
									"   while (y > 1) {\n"	// 4
									"       y = y + 1;\n"	// 5
									"		if (!((y == 0) && (z >= 0))) then {\n"	// 6
									"			z = z + 1; }\n"		// 7
									"		else {"			
									"			z = z - 1; }\n"		// 8
									"	}"	
									"   read x;\n"	// 9
									"   while (y > 5) {\n"	// 10
									"       z = z + 1;}}\n"	// 11
									"procedure proc2 {"
									"   read x;"	// 12
									"   if (y > 1) then {"	// 13
									"       print k;"	// 14
									"       y = y + 1; }"		// 15
									"	else {"
									"		z = z + 1; "	// 16
									"		while (a < 0 - b * c) {"	// 17
									"			a = a + 1; }"		// 18
									"	}"
									"   read x; "		// 19
									"	call proc1; }";		// 20

		std::ofstream file;
		file.open(filename);
		file << sampleProgram;
		file.close();
		
		REQUIRE(std::filesystem::exists(filename));
		SourceProcessor sp = SourceProcessor(filename, pkbManager);
		std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();

		sp.parseSIMPLE();
		sp.extractAndPopulate();

		std::shared_ptr<StatementReader> statementReader = pkbReaderManager->getStatementReader();
		std::shared_ptr<NextReader> nextReader = pkbReaderManager->getNextReader();
		std::shared_ptr<NextTReader> nextTReader = pkbReaderManager->getNextTReader();

		std::unordered_set<int> expectedStatements = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
		REQUIRE(statementReader->getAllStatements() == expectedStatements);

		std::unordered_set<int> expectedNextOf1 = { 2 };
		REQUIRE(nextReader->getNext(1) == expectedNextOf1);

		std::unordered_set<int> expectedNextOf3 = { 4 };
		REQUIRE(nextReader->getNext(3) == expectedNextOf3);

		std::unordered_set<int> expectedNextOf4 = { 5, 9 };
		REQUIRE(nextReader->getNext(4) == expectedNextOf4);

		std::unordered_set<int> expectedNextOf6 = { 7, 8 };
		REQUIRE(nextReader->getNext(6) == expectedNextOf6);

		std::unordered_set<int> expectedNextOf7 = { 4 };
		REQUIRE(nextReader->getNext(7) == expectedNextOf7);

		std::unordered_set<int> expectedNextOf8 = { 4 };
		REQUIRE(nextReader->getNext(8) == expectedNextOf8);

		std::unordered_set<int> expectedNextOf10 = { 11 };
		REQUIRE(nextReader->getNext(10) == expectedNextOf10);

		std::unordered_set<int> expectedNextOf11 = { 10 };
		REQUIRE(nextReader->getNext(11) == expectedNextOf11);

		std::unordered_set<int> expectedNextOf12 = { 13 };
		REQUIRE(nextReader->getNext(12) == expectedNextOf12);

		std::unordered_set<int> expectedNextOf13 = { 14, 16 };
		REQUIRE(nextReader->getNext(13) == expectedNextOf13);

		std::unordered_set<int> expectedNextOf17 = { 18, 19 };
		REQUIRE(nextReader->getNext(17) == expectedNextOf17);

		std::unordered_set<int> expectedNextOf19 = { 20 };
		REQUIRE(nextReader->getNext(19) == expectedNextOf19);

		std::unordered_set<int> expectedNextOf20 = {};
		REQUIRE(nextReader->getNext(20) == expectedNextOf20);

		std::unordered_set<int> expectedPreviousOf7 = { 6 };
		REQUIRE(nextReader->getPrevious(7) == expectedPreviousOf7);

		std::unordered_set<int> expectedPreviousOf9 = { 4 };
		REQUIRE(nextReader->getPrevious(9) == expectedPreviousOf9);

		std::unordered_set<int> expectedPreviousOf12 = {};
		REQUIRE(nextReader->getPrevious(12) == expectedPreviousOf12);

		std::unordered_set<int> expectedPreviousOf17 = { 16, 18 };
		REQUIRE(nextReader->getPrevious(17) == expectedPreviousOf17);

		std::unordered_set<int> expectedPreviousOf19 = { 15, 17 };
		REQUIRE(nextReader->getPrevious(19) == expectedPreviousOf19);

		std::unordered_set<int> expectedAllNext = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 13, 14, 15, 16, 17, 18, 19, 20 };
		REQUIRE(nextReader->getAllNext() == expectedAllNext);

		std::unordered_set<int> expectedAllPrevious = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19 };
		REQUIRE(nextReader->getAllPrevious() == expectedAllPrevious);

		std::unordered_set<int> expectedNextTOf1 = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
		REQUIRE(nextTReader->getNextT(1) == expectedNextTOf1);

		std::unordered_set<int> expectedPrevioustTof20 = { 19, 18, 17, 16, 15, 14, 13, 12 };
		REQUIRE(nextTReader->getPreviousT(20) == expectedPrevioustTof20);

		std::filesystem::remove(filename);
	}
}