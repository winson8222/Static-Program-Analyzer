#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Constants") {
    SECTION("Basic Constants") {
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
        std::shared_ptr<ConstantReader> constantReader = pkbReaderManager->getConstantReader();
        std::unordered_set<int> expectedConstants = { 1, 2, 6 };
        REQUIRE(constantReader->getAllConstants() == expectedConstants);

        std::filesystem::remove(filename);
    }

    SECTION("Constants in Expressions") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1;"
                                    "   y = 2;"
                                    "   z = 1 + 2;"
                                    "   a = 1 + 2 * 3;"
                                    "   b = 1 + 2 * 3 + 4;"
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
        std::shared_ptr<ConstantReader> constantReader = pkbReaderManager->getConstantReader();
        std::unordered_set<int> expectedConstants = { 1, 2, 3, 4 };
        REQUIRE(constantReader->getAllConstants() == expectedConstants);

        std::filesystem::remove(filename);
    }

    SECTION("Large Constants") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
        std::string filename = "sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   x = 1010010101;"
                                    "   y = 1010010102;"
                                    "   z = 1010010103;"
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
        std::shared_ptr<ConstantReader> constantReader = pkbReaderManager->getConstantReader();
        std::unordered_set<int> expectedConstants = { 1010010101, 1010010102, 1010010103 };
        REQUIRE(constantReader->getAllConstants() == expectedConstants);

        std::filesystem::remove(filename);


    }
}