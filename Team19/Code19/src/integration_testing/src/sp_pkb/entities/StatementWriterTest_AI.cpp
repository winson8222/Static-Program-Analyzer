#include "catch.hpp"

#include <filesystem>
#include <fstream>
#include <memory>

#include "pkb/PKBManager.h"
#include "sp/SourceProcessor.h"

TEST_CASE("sp/SourceProcessor: Statement") {
    SECTION("Basic Statement") {
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
        std::shared_ptr<StatementReader> statementReader = pkbReaderManager->getStatementReader();
        std::unordered_set<int> expectedStatements = { 1, 2, 3, 4 };
        REQUIRE(statementReader->getAllStatements() == expectedStatements);

        std::filesystem::remove(filename);
    }
}