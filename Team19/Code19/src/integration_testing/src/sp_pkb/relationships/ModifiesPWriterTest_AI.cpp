#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: ModifiesP") {
    SECTION("Procedure/Call ModifiesS") {
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
            "   call proc1; "
            "   t = 4 + y + x + i + u; }"
            "procedure proc3 {"
            "call proc2;" 
            "s = 0; }";

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
        std::shared_ptr<ModifiesPReader> modifiesPReader = pkbReaderManager->getModifiesPReader();
        REQUIRE(modifiesPReader->getAllVariablesModifiedByProc("proc1") == std::unordered_set<std::string>({ "x", "y", "z", "t" }));
        REQUIRE(modifiesPReader->getAllVariablesModifiedByProc("proc2") == std::unordered_set<std::string>({ "x", "y", "z", "t" }));
        REQUIRE(modifiesPReader->getAllVariablesModifiedByProc("proc3") == std::unordered_set<std::string>({ "x", "y", "z", "t", "s" }));
        REQUIRE(modifiesReader->getAllVariablesModifiedByStmt(12) == std::unordered_set<std::string>({ "x", "y", "z", "t" }));
        REQUIRE(modifiesReader->getAllVariablesModifiedByStmt(14) == std::unordered_set<std::string>({ "x", "y", "z", "t" }));
    }
}