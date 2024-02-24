#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Read") {
    SECTION("Basic Read") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   read x;"
                                    "   y = 2;"
                                    "   read y;"
                                    "   while (z > 1) {"
                                    "       z = z + 1; }"
                                    "}"
                                    "procedure proc2 {"
                                    "   read z;"
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
        std::shared_ptr<ReadReader> readReader = pkbReaderManager->getReadReader();
        std::unordered_set<int> expectedReads = { 1, 3, 6 };
        REQUIRE(readReader->getAllReads() == expectedReads);

        std::filesystem::remove(filename);
    }
}