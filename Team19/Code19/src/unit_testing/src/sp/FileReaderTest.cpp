#include "sp/Tokenizer.h"
#include "catch.hpp"

TEST_CASE("Tokenizer::readFileToString", "[readFileToString]") {
    const std::string testFileName = "../../../tests/sourcefile1.txt";
    const std::string testFileContent = "This is a test file content.";

    // Write the test content to the temporary file
    std::ofstream tempFile(testFileName);
    REQUIRE(tempFile.is_open());
    tempFile << testFileContent;
    tempFile.close();

    std::string actualContent;
    REQUIRE_NOTHROW(actualContent = Tokenizer::readFileToString(testFileName));
    REQUIRE(actualContent == testFileContent);

    // Remove the temporary test file
    std::remove(testFileName.c_str());
}

