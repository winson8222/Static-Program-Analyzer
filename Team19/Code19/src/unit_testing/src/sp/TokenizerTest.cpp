#include "sp/Tokenizer.h"
#include "catch.hpp"
#include <fstream>
#include <filesystem>
#include <vector>


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

}