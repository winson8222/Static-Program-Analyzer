#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Follows") {
    SECTION("Basic Follows") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();

        std::string filename = "./sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   read x;"
                                    "   while (y > 1) {"
                                    "       y = y + 1;"
                                    "   }"
                                    "   read x;"
                                    "   while (y > 5) {"
                                    "       z = z + 1;"
                                    "   }"
                                    "}"
                                    "procedure proc2 {"
                                    "   read x;"
                                    "   while (y > 1) {"
                                    "       y = y + 1;"
                                    "   }"
                                    "   read x;"
                                    "}";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();

        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
        std::shared_ptr<FollowsWriter> followsWriter = pkbWriterManager->getFollowsWriter();
        followsWriter->clear();

        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();

        std::shared_ptr<FollowsReader> followsReader = pkbReaderManager->getFollowsReader();
        std::unordered_set<int> expectedFollows = { 1, 2, 4, 7, 8 };
        REQUIRE(followsReader->getAllPreFollows() == expectedFollows);

        std::filesystem::remove(filename);
    }

    SECTION("Follows with nested whiles") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();

        std::string filename = "./sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   read x;" // 1
                                    "   while (y > 1) {" // 2
                                    "       y = y + 1;" // 3
                                    "       while (z > 1) {"
                                    "           z = z + 1;"
                                    "       }"
                                    "   }"
                                    "   read x;" // 6
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
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
        std::shared_ptr<FollowsWriter> followsWriter = pkbWriterManager->getFollowsWriter();
        followsWriter->clear();

        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();

        std::shared_ptr<FollowsReader> followsReader = pkbReaderManager->getFollowsReader();
        std::unordered_set<int> expectedPreFollows = { 1, 2, 3, 6 };
        REQUIRE(followsReader->getAllPreFollows() == expectedPreFollows);
        std::unordered_set<int> expectedPostFollows = {2, 4, 6, 7};
        REQUIRE(followsReader->getAllPostFollows() == expectedPostFollows);

        std::filesystem::remove(filename);
    }

    SECTION("No Follows") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();

        std::string filename = "./sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   while (y > 1) {"
                                    "       y = y + 1;"
                                    "   }"
                                    "}";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();

        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
        std::shared_ptr<FollowsWriter> followsWriter = pkbWriterManager->getFollowsWriter();
        followsWriter->clear();

        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();

        std::shared_ptr<FollowsReader> followsReader = pkbReaderManager->getFollowsReader();
        std::unordered_set<int> expectedPreFollows = {};
        REQUIRE(followsReader->getAllPreFollows() == expectedPreFollows);
        std::unordered_set<int> expectedPostFollows = {};
        REQUIRE(followsReader->getAllPostFollows() == expectedPostFollows);

        std::filesystem::remove(filename);
    }
}