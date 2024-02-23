#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Assigns") {
    SECTION("Basic Assigns") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1;"
                                    "   y = 2;"
                                    "}"
                                    "procedure proc2 {"
                                    "   z = 1;"
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
        std::shared_ptr<AssignReader> assignReader = pkbReaderManager->getAssignReader();
        std::unordered_set<int> expectedAssigns = { 2, 3, 6, 7 };
        REQUIRE(assignReader->getAllAssigns() == expectedAssigns);

        std::filesystem::remove(filename);
    }
}