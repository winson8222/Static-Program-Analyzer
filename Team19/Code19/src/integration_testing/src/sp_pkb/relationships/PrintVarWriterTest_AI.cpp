#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: PrintVar") {
    SECTION("Basic PrintVar") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
            "   print x;"
            "   y = 2;"
            "   print y;"
            "   if (z > 1) then {"
            "       print thisForMePlease3; }"
            "   else { read Supercalifragilisticexpialidocious; }"
            "}"
            "procedure proc2 {"
            "   print somePaper4;"
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
        std::shared_ptr<PrintVarNameReader> printVarNameReader = pkbReaderManager->getPrintVarNameReader();
        std::unordered_set<int> expectedPrints = { 1, 3, 5, 7 };
        REQUIRE(printReader->getAllPrints() == expectedPrints);

        std::unordered_set<std::string> expectedPrintVariables = { "x", "y", "thisForMePlease3", "somePaper4" };
        REQUIRE(printVarNameReader->getAllPrintVariables() == expectedPrintVariables);

        std::filesystem::remove(filename);
    }
}