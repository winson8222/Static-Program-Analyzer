#include "sp/Tokenizer.h"
#include "catch.hpp"
#include <fstream>
#include <filesystem>

TEST_CASE("Tokenizer::readFileToString", "[readFileToString]") {
    const std::string testFileName = "../../../../../tests/sourcefile1.txt";
    const std::string testFileContent = "x = 1;";
    REQUIRE(std::filesystem::exists(testFileName));

    std::string actualContent;
    REQUIRE_NOTHROW(actualContent = Tokenizer::readFileToString(testFileName));
    REQUIRE(actualContent == testFileContent);

    // Tokenizer::tokenize(actualContent);
}