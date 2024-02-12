#include "sp/Tokenizer.h"
#include "sp/SourceProcessor.h"
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

TEST_CASE("Test parser of SP", "[SourceProcessor]") {
    std::cout << "\n\nSP-WORKFLOW-TEST STARTS\n\n\n" << std::endl;
    const std::string testFileName = "../../../../../tests/sp/ParserTest/CallStmt1.txt";
    const std::string testFileContent = "x = 1;";

    std::string actualContent;
    REQUIRE(std::filesystem::exists(testFileName));

    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    SourceProcessor sp(testFileName, pkbManager);

    REQUIRE_NOTHROW(sp.parseSIMPLE());
    REQUIRE_NOTHROW(sp.extractAndPopulate());

    std::shared_ptr<PKBReader> pkbReader = pkbManager->getPKBReader();

    auto values1 = pkbReader->getAllVariables();
    std::cout << "All Extracted variables: ";
    for (auto& var : values1) {
        std::cout << var << ", ";
    }
    std::cout << std::endl;

    std::cout << "SP-WORKFLOW-TEST ENDS\n\n\n" << std::endl;
}