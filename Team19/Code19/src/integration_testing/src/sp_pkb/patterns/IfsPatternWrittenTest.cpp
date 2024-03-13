#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: IfPattern") {
	SECTION("Basic IfPattern") {
		std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();

		std::string filename = "./sample.txt";
		std::string sampleProgram = "procedure proc1 {"
			"   if (a > 1) then {"	// 1
			"       a = a - 1 * 4; "
			"	} else {"
			"		read x; "
			"   }"
			"   if ((y > 5) && (z == y)) then {"	// 4
			"       z = z + 1; "
			"	} else {"
			"		print z; "
			"	}"
			"}"
			"procedure proc2 {"
			"   if (a == 0) then {"		// 7
			"       if (b != 0) then {"		// 8
			"           if (!(c == 0)) then {"		// 9
			"               read x;"
			"           } else {"
			"               print x; "
			"			}"
			"		} else {"
			"           read x; "
			"		}"
			"	} else {"
			"       if (!((a <= 0) || (a > 0))) then {"		// 13
			"			a = a + 1;"
			"		} else {"
			"			read x; "
			"		}"
			"   }"
			"}"
			;
		std::ofstream file;
		file.open(filename);
		file << sampleProgram;
		file.close();

		REQUIRE(std::filesystem::exists(filename));
		SourceProcessor sp = SourceProcessor(filename, pkbManager);
		std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();

		sp.parseSIMPLE();
		sp.extractAndPopulate();

		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
		std::shared_ptr<IfPatternReader> ifPatternReader = pkbReaderManager->getIfPatternReader();

		std::unordered_set<int> expectedIfPattern1 = { 1, 4, 7, 8, 9, 13 };
		REQUIRE(ifPatternReader->getAllStatementNumbers() == expectedIfPattern1);

		std::unordered_set<std::string> expectedIfPattern2 = { "a", "y", "z", "b", "c" };
		REQUIRE(ifPatternReader->getAllIfControlVariables() == expectedIfPattern2);

		std::unordered_set<int> expectedIfPattern3 = { 1, 7, 13 };
		REQUIRE(ifPatternReader->getStatementNumbersOfIfControlVariable("a") == expectedIfPattern3);

		std::unordered_set<int> expectedIfPattern4 = { 4 };
		REQUIRE(ifPatternReader->getStatementNumbersOfIfControlVariable("z") == expectedIfPattern4);

		std::unordered_set<std::string> expectedIfPattern5 = { "y", "z" };
		REQUIRE(ifPatternReader->getControlVariablesOfIfStatement(4) == expectedIfPattern5);

		std::unordered_set<std::string> expectedIfPattern6 = { "a"};
		REQUIRE(ifPatternReader->getControlVariablesOfIfStatement(13) == expectedIfPattern6);

		std::filesystem::remove(filename);
	}

}