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
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1;"
                                    "   y = 2; }"
                                    "procedure proc2 {"
                                    "   z = 1;"
                                    "   print z;"
                                    "   y = 6 * z;"
                                    "   while (z > 1) {"
                                    "       z = z + 1; }"
                                    "   if (z > 1) then {"
                                    "       z = z + 1; "
                                    "   } else {"
                                    "       z = z + 1;"
                                    "       x = 4; "
                                    "       while (z > 1) {"
                                    "           z = z + 1; }}}";
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
        REQUIRE(parentTReader->getChildT(1).empty());
        REQUIRE(parentTReader->getAllChildrenT() == std::unordered_set<int>{7, 9, 10, 11, 12, 13});

        REQUIRE(parentTReader->getKeys() == std::unordered_set<int>{6, 8, 12});

        REQUIRE(parentTReader->getParentT(13) == std::unordered_set<int>{8, 12});
        REQUIRE(parentTReader->getParentT(12) == std::unordered_set<int>{8});
        REQUIRE(parentTReader->getParentT(11) == std::unordered_set<int>{8});

    }
}