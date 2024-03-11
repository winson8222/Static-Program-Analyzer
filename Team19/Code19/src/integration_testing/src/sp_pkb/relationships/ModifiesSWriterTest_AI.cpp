#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: ModifiesS") {
SECTION("Basic ModifiesS") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1;"
                                    "   y = 2; }"
                                    "procedure proc2 {"
                                    "   z = 1;"
                                    "   read z;"
                                    "   y = 6 * z;"
                                    "   while (z > 1) {"
                                    "       y = z + 1; "
                                    "       z = z + 1; }}";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<ModifiesSReader> modifiesReader = pkbReaderManager->getModifiesSReader();
        REQUIRE(modifiesReader->doesStmtModifyVariable(1, "x"));
        REQUIRE(modifiesReader->getAllStmtsThatModifyVariable("y") == std::unordered_set<int>({2, 5, 6, 7}));
        REQUIRE(modifiesReader->getAllStmtsThatModifyVariable("z") == std::unordered_set<int>({3, 4, 6, 8}));
        REQUIRE(modifiesReader->getAllVariablesModifiedByStmt(6) == std::unordered_set<std::string>({"y", "z"}));
        std::filesystem::remove(filename);
    }
    SECTION("Container ModifiesS") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1;"
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
        std::shared_ptr<ModifiesSReader> modifiesReader = pkbReaderManager->getModifiesSReader();
        REQUIRE(modifiesReader->doesStmtModifyVariable(1, "x"));
        REQUIRE(modifiesReader->getAllStmtsThatModifyVariable("x") ==
                std::unordered_set<int>({1, 2, 4, 5, 10, 11}));

    }
}
