#include "sp/SPTokenizer/SPTokenizer.h"
#include "sp/SourceProcessor.h"
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

TEST_CASE("Test header", "[SourceProcessor]") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure main {"
                                "read helloWorld;"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));

    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    SourceProcessor sp(filename, pkbManager);

    REQUIRE_NOTHROW(sp.parseSIMPLE());
    REQUIRE_NOTHROW(sp.extractAndPopulate());

    std::shared_ptr<PKBReaderManager> pkbReaderManager = sp.pkbManager->getPKBReaderManager();
    auto variableReader = pkbReaderManager->getVariableReader();
    auto values1 = variableReader->getAllVariables();
    std::filesystem::remove(filename);
}
