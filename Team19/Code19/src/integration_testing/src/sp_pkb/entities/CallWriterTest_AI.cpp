#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Calls") {
    SECTION("Basic Calls") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1;"
                                    "   call proc2;"
                                    "}"
                                    "procedure proc2 {"
                                    "   z = 1;"
                                    "   call proc3;"
                                    "}"
                                    "procedure proc3 {"
                                    "   y = 6 * z;"
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
        std::shared_ptr<CallReader> callReader = pkbReaderManager->getCallReader();
        std::unordered_set<int> expectedCalls = { 2, 4 };
        REQUIRE(callReader->getAllCalls() == expectedCalls);

        std::filesystem::remove(filename);
    }
}