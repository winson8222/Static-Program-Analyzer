#include "sp/Tokenizer.h"
#include "catch.hpp"
#include <fstream>
#include <filesystem>

TEST_CASE("Tokenizer::splitLIne", "[splitLine]") {
    const std::string testFileName = "../../../../../tests/sourcefile1.txt";
    const std::string testFileContent = "x = 1;";
    REQUIRE(std::filesystem::exists(testFileName));

    std::string actualContent = Tokenizer::readFileToString(testFileName);
    INFO("Actual content:\n" << actualContent);
    std::cout << "Kill me" << std::endl;
}