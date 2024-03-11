#include "catch.hpp"
#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Parent") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1;"     // statement 1
                                    "   y = 2; }"   // statement 2
                                    "procedure proc2 {"
                                    "   z = 1;"     // statement 3
                                    "   print z;"   // statement 4
                                    "   y = 6 * z;" // statement 5
                                    "   while (z > 1) {"    // statement 6
                                    "       z = z + 1;"
                                    "   }" // statement 7
                                    "   if (z > 1) then {"  // statement 8
                                    "       z = z + 1; "    // statement 9
                                    "   } else {"
                                    "       z = z + 1;"     // statement 10
                                    "       x = 4; "        // statement 11
                                    "       while (z > 1) {"    // statement 12
                                    "           z = z + 1; }}}";   // statement 13
                                    
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
        parentReader->getAllParents();
        parentReader->getChild(8);
        parentReader->getParent(12);
        parentReader->getAllChildren();
        REQUIRE(parentReader->getAllParents() == std::unordered_set<int>({6, 8, 12}));
        REQUIRE(parentReader->getChild(8) == std::unordered_set<int>({ 9, 10, 11, 12 }));
        REQUIRE(parentReader->getParent(12) == std::unordered_set<int>({ 8 }));
        REQUIRE(parentReader->getAllChildren() == std::unordered_set<int>({ 7, 9, 10, 11, 12, 13 }));
        std::filesystem::remove(filename);
}
