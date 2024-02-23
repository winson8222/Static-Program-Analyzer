#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "sp/SourceProcessor.h"
#include "pkb/PKBManager.h"

TEST_CASE("sp/SourceProcessor: Whiles") {
    SECTION("Basic Whiles") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   read x;"
                                    "   while (y > 1) {"
                                    "       y = y + 1;"
                                    "   }"
                                    "   read x;"
                                    "   while (y > 5) {"
                                    "       z = z + 1;"
                                    "   }"
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
        std::shared_ptr<WhileReader> whileReader = pkbReaderManager->getWhileReader();
        std::unordered_set<int> expectedWhiles = { 3, 7 };
        REQUIRE(whileReader->getAllWhiles() == expectedWhiles);

        std::filesystem::remove(filename);
    }


}