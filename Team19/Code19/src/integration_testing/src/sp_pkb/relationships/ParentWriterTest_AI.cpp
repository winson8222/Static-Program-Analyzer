#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Parent") {
    SECTION("Basic Parent") {
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
                                    "       z = z + 1; }}";
//                                    "   if (z > 1) then {"
//                                    "       z = z + 1; "
//                                    "   } else {"
//                                    "       z = z + 1;"
//                                    "       x = 4; "
//                                    "       while (z > 1) {"
//                                    "           z = z + 1; }"
//                                    "   }"
//                                    "   print z; }";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();
        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();
        std::shared_ptr<ParentReader> parentReader = pkbReaderManager->getParentReader();
        REQUIRE(parentReader->getAllParents() == std::unordered_set<int>({6, 8, 12}));
        REQUIRE(parentReader->getChild(8) == std::unordered_set<int>({ 9, 10, 11, 12 }));
        REQUIRE(parentReader->getParent(12) == std::unordered_set<int>({ 8 }));
        REQUIRE(parentReader->getAllChildren() == std::unordered_set<int>({ 7, 9, 10, 11, 12, 13 }));
        std::filesystem::remove(filename);
    }
}
