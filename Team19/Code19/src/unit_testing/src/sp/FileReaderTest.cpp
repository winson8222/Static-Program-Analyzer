#include "sp/Tokenizer.h"
#include "catch.hpp"
#include <fstream>

TEST_CASE("Tokenizer::readFileToString", "[readFileToString]") {
    const std::string testFileName = "../../../../../tests/sourcefile1.txt";
    const std::string testFileContent = "This is a test file content.";
    // Initialize the tempFile variable
    std::ofstream tempFile;

    // Open the test file and check if it's open
    tempFile.open(testFileName);
    REQUIRE(tempFile.is_open());
    tempFile << testFileContent;
    tempFile.close();

    std::string actualContent;
    REQUIRE_NOTHROW(actualContent = Tokenizer::readFileToString(testFileName));

    // Assert that the actual content matches the expected content
    REQUIRE(actualContent == testFileContent);

    // Remove the temporary test file
    std::remove(testFileName.c_str());
}