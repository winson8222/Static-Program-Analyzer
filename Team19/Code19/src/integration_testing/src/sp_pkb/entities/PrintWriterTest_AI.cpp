#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Print") {
    SECTION("Basic Print") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   print x;"
                                    "   print y;"
                                    "}"
                                    "procedure proc2 {"
                                    "   print z;"
                                    "   read x;"
                                    "   print y;"
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
        std::shared_ptr<PrintReader> printReader = pkbReaderManager->getPrintReader();
        std::unordered_set<int> expectedPrints = { 1, 2, 3, 5 };
        REQUIRE(printReader->getAllPrints() == expectedPrints);

        std::filesystem::remove(filename);
    }
}