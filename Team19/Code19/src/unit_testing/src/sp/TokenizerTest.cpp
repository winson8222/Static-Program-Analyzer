#include "sp/Tokenizer.h"
#include "catch.hpp"
#include <fstream>
#include <filesystem>
#include <vector>

TEST_CASE("Tokenizer::readFileToString", "[readFileToString]") {
    const std::string testFileName = "../../../../../tests/sourcefile1.txt";
    const std::string testFileContent = "x = 1;";
    REQUIRE(std::filesystem::exists(testFileName));

    std::string actualContent;
    REQUIRE_NOTHROW(actualContent = Tokenizer::readFileToString(testFileName));
    REQUIRE(actualContent == testFileContent);

    Tokenizer::tokenize(actualContent);
}

TEST_CASE("Tokenizer::splitLine", "[splitLine]") {
    const std::string testFileName = "../../../../../tests/sourcefile2.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    const std::vector<std::string> expectedOutput = {
        "procedure testproc {",
        "   x = 1;",
        "   y = 2;",
        "   z = x + y;",
        "}"
    };

    std::string actualContent = Tokenizer::readFileToString(testFileName);
    std::vector<std::string> actualOutput = Tokenizer::splitLine(actualContent);

    REQUIRE(actualOutput == expectedOutput);
    const int expectedLineNumber = 5;
    REQUIRE(actualOutput.size() == expectedLineNumber);

    Tokenizer::tokenize(actualContent);
}