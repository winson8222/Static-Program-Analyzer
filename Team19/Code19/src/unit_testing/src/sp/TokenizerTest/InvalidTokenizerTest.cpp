#include "sp/SPTokenizer/SPTokenizer.h"
#include "sp/SPTokenizer/LexicalToken.h"
#include "sp/SPTokenizer/FileProcessor.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <regex>

TEST_CASE("Tokenizer invalid cases", "[readFileToString]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile6.txt";
    const std::string testFileContent = "x = 1;";
    REQUIRE(std::filesystem::exists(testFileName));

    std::string actualContent;
    REQUIRE_NOTHROW(actualContent = FileProcessor::readFileToString(testFileName));
    auto arr = SPTokenizer::tokenize(actualContent);
}