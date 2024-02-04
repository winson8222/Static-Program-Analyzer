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

    // Print the actual content and expected content for debugging
    INFO("Actual content:\n" << actualContent);
    INFO("Expected content:\n" << testFileContent);

    // Assert that the actual content matches the expected content
    REQUIRE(actualContent == testFileContent);
}