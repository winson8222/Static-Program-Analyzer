#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: ReadVar") {
    SECTION("Basic ReadVar") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
            "   read x;"
            "   y = 2;"
            "   read y;"
            "   while (z > 1) {"
            "       read thisForMePlease3; }"
            "   read Supercalifragilisticexpialidocious;"
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
        std::shared_ptr<ReadVarNameReader> readVarNameReader = pkbReaderManager->getReadVarNameReader();
        std::unordered_set<int> expectedReads = { 1, 3, 5, 6, 7 };
        REQUIRE(readReader->getAllReads() == expectedReads);

        std::unordered_set<std::string> expectedReadVariables = { "x", "y", "thisForMePlease3", "Supercalifragilisticexpialidocious", "z" };
        REQUIRE(readVarNameReader->getAllReadVariables() == expectedReadVariables);

        std::filesystem::remove(filename);
    }
}