#include "sp/Tokenizer.h"
#include "sp/SourceProcessor.h"
#include "catch.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

TEST_CASE("Test header", "[SourceProcessor]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile1.txt";
    const std::string testFileContent = "x = 1;";

    std::string actualContent;
    REQUIRE(std::filesystem::exists(testFileName));

    PKBManager pkbManager;
    SourceProcessor sp(pkbManager);

    REQUIRE_NOTHROW(sp.tokenize(Tokenizer::readFileToString(testFileName)));
    REQUIRE_NOTHROW(sp.extractAndPopulate());

    std::shared_ptr<PKBReader> pkbReader = sp.pkbManager.getPKBReader();
    
    auto values = pkbReader->getAllVariables();
}