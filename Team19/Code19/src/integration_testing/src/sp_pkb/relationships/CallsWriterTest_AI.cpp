#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Calls Procedure") {
    SECTION("Uses in Procedure and Call for invokes") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
            "   x = 1 + u;"     // 1
            "   while (x < 10) {"   // 2
            "       y = 2 + x; "    // 3
            "       x = p + 1;}"    // 4
            "    if (x > 10) then {"        // 5
            "       z = 3 + x; "        // 6
            "       t = 4 + y + x + i + u; "    // 7
            "       } else {"
            "           z = 3 + x; "    // 8
            "           t = 4 + y + x + i + u; "    // 9
            "       while (x < 10) {"   // 10
            "           x = 3 + y; }}}"   // 11
            "procedure proc2 {"
            "   z = 3 + x; "    // 12
            "   call proc1; }"     // 13
            "procedure proc3 {"
            "me = meme;"    // 14
            "call proc2; }"// 15
            "procedure proc4 {"
            "call proc2;"   // 16
            "call proc3; }";    // 17
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<CallReader> callReader = pkbReaderManager->getCallReader();
        std::shared_ptr<CallsReader> callsReader = pkbReaderManager->getCallsReader();
        std::shared_ptr<CallsTReader> callsTReader = pkbReaderManager->getCallsTReader();

    }
}