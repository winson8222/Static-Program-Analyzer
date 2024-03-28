#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"


TEST_CASE("sp/SourceProcessor: ParentT") {
    SECTION("Basic ParentT") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc0 {"
            "   if (a + (b -x) * 4 > 0) then {"     // 1
            "       x = 1; } else {"                // 2
            "       print c; }}"         // 3       
            "procedure proc1 {"
            "   x = 1;"         // 4
            "   y = 2; }"       // 5
            "procedure proc2 {"
            "   z = 1;"         // 6
            "   print z;"       // 7
            "   y = 6 * z;"     // 8
            "   while (z > 1) {"        // 9
            "       z = z + 1; }"       // 10
            "   if (z > 1) then {"      // 11
            "       z = z + 1; "        // 12
            "   } else {"
            "       z = z + 1;"         // 13
            "       x = 4; "            // 14
            "       while (z > 1) {"    // 15
            "           z = z + 1; }"   // 16
            "       call proc1;"        // 17
            "   call proc0; }"          // 18
            "}";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<ParentTReader> parentTReader = pkbReaderManager->getParentTReader();

        REQUIRE(parentTReader->getParentT(1) == std::unordered_set<int>());
        std::unordered_set<int> expectedParentT1 = { 1 };
        REQUIRE(parentTReader->getParentT(2) == expectedParentT1);
        REQUIRE(parentTReader->getParentT(3) == expectedParentT1);

        REQUIRE(parentTReader->getParentT(4) == std::unordered_set<int>());
        REQUIRE(parentTReader->getParentT(5) == std::unordered_set<int>());

        REQUIRE(parentTReader->getParentT(9) == std::unordered_set<int>());
        std::unordered_set<int> expectedParentT2 = { 9 };
        REQUIRE(parentTReader->getParentT(10) == expectedParentT2);

        std::unordered_set<int> expectedParentT3 = { 11, 15 };
        REQUIRE(parentTReader->getParentT(16) == expectedParentT3);

        std::unordered_set<int> expectedParentT4 = { 11 };
        REQUIRE(parentTReader->getParentT(17) == expectedParentT4);

        std::unordered_set<int> expectedParentT5 = { 11 };
        REQUIRE(parentTReader->getParentT(18) == expectedParentT5);
    }
}