#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: If") {
    SECTION("Basic If") {
        std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();

        std::string filename = "./sample.txt";
        std::string sampleProgram = "procedure proc1 {"
                                    "   if (x > 1) then {"
                                    "       y = 1;"
                                    "   } else {"
                                    "       z = 1;"
                                    "   }"
                                    "   if (y > 1) then {"
                                    "       z = 1;"
                                    "   } else {"
                                    "       z = 1;"
                                    "   }"
                                    "}";
        std::ofstream file;
        file.open(filename);
        file << sampleProgram;
        file.close();

        REQUIRE(std::filesystem::exists(filename));
        SourceProcessor sp = SourceProcessor(filename, pkbManager);
        std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
        std::shared_ptr<IfWriter> ifWriter = pkbWriterManager->getIfWriter();
        ifWriter->clear();

        sp.parseSIMPLE();
        sp.extractAndPopulate();
        std::shared_ptr<PKBReaderManager> pkbReaderManager = pkbManager->getPKBReaderManager();

        std::shared_ptr<IfReader> ifReader = pkbReaderManager->getIfReader();
        std::unordered_set<int> expectedIfs = { 1, 4 };
        REQUIRE(ifReader->getAllIfs() == expectedIfs);

        std::filesystem::remove(filename);
    }
}