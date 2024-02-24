#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: FollowsT") {
    SECTION("Basic FollowsT") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();

        std::string filename = "./sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   read x;" // 1
                                    "   while (y > 1) {"
                                    "       y = y + 1; }"
                                    "   read x;"
                                    "   while (y > 5) {"
                                    "       z = z + 1;}}"
                                    "procedure proc2 {"
                                    "   read x;"
                                    "   while (y > 1) {"
                                    "       y = y + 1; }"
                                    "   read x; }";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();

        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
        std::shared_ptr<FollowsTWriter> followsTWriter = pkbWriterManager->getFollowsTWriter();
        followsTWriter->clear();

        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();

        std::shared_ptr<FollowsTReader> followsTReader = pkbReaderManager->getFollowsTReader();
        std::unordered_set<int> expectedFollowsT = { 1, 2, 4, 7, 8 };
        REQUIRE(followsTReader->getAllPreFollowsT() == expectedFollowsT);

        REQUIRE(followsTReader->getPostFollowsT(1) == std::unordered_set<int>({ 2, 4, 5 }));
        REQUIRE(followsTReader->getPostFollowsT(2) == std::unordered_set<int>({ 4, 5 }));
        REQUIRE(followsTReader->getPostFollowsT(4) == std::unordered_set<int>({ 5 }));


        std::filesystem::remove(filename);
    }
}