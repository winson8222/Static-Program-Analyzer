#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: UsesS") {
    SECTION("Basic UsesS") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1 + u;"
                                    "   y = 2 + x; }"
                                    "procedure proc2 {"
                                    "   z = 3 + x; "
                                    "   t = 4 + y + x + i + u;"
                                    "   print gg; }";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<UsesSReader> usesReader = pkbReaderManager->getUsesSReader();
        REQUIRE(usesReader->doesStmtUseVariable(1, "u"));
        REQUIRE(usesReader->getAllStmtsThatUseVariable("x") == std::unordered_set<int>({2, 3, 4}));
        REQUIRE(usesReader->getAllStmtsThatUseVariable("y") == std::unordered_set<int>({4}));
        REQUIRE(usesReader->getAllVariablesUsedByStmt(4) == std::unordered_set<std::string>({"x", "y", "i", "u"}));
        REQUIRE(usesReader->getAllStmtsThatUseVariable("gg") == std::unordered_set<int>({5}));
    }
    SECTION("Container UsesS") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1 + u;"
                                    "   while (x < 10) {"
                                    "       y = 2 + x; "
                                    "       x = p + 1;}"
                                    "    if (x > 10) then {"
                                    "       z = 3 + x; "
                                    "       t = 4 + y + x + i + u; "
                                    "       } else {"
                                    "           z = 3 + x; "
                                    "           t = 4 + y + x + i + u; "
                                    "       while (x < 10) {"
                                    "           x = 3 + y; }}}"
                                    "procedure proc2 {"
                                    "   z = 3 + x; "
                                    "   t = 4 + y + x + i + u; }";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<UsesSReader> usesReader = pkbReaderManager->getUsesSReader();
        REQUIRE(usesReader->doesStmtUseVariable(1, "u"));
        REQUIRE(usesReader->getAllStmtsThatUseVariable("x") == std::unordered_set<int>({2, 3, 5, 6, 7, 8, 9, 10, 12, 13}));
        REQUIRE(usesReader->getAllVariablesUsedByStmt(2) == std::unordered_set<std::string>({"x", "p"}));
        REQUIRE(usesReader->getAllVariablesUsedByStmt(10) == std::unordered_set<std::string>({"x", "y"}));
    }
}
