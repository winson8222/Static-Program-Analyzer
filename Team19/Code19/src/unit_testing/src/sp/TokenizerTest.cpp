#include "sp/Tokenizer.h"
#include "catch.hpp"
#include <fstream>
#include <filesystem>
#include <vector>

TEST_CASE("Tokenizer::readFileToString", "[readFileToString]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile1.txt";
    const std::string testFileContent = "x = 1;";
    REQUIRE(std::filesystem::exists(testFileName));

    std::string actualContent;
    REQUIRE_NOTHROW(actualContent = Tokenizer::readFileToString(testFileName));
    REQUIRE(actualContent == testFileContent);

    Tokenizer::tokenize(actualContent);
}

// ai-gen start(gpt,1,e)
// prompt: https://platform.openai.com/playground?thread=thread_B0hJ2obSjkZeF7NDPIUidhBG
TEST_CASE("Test reading non-existent file", "[readFileToString]") {
    Tokenizer tokenizer;
    REQUIRE_THROWS_WITH(tokenizer.readFileToString("non_existent_file.txt"),
        "Error: Unable to open the input file.");
}

TEST_CASE("Test reading from an empty file", "[readFileToString]") {
    // Assume empty.txt is a blank file in ../files directory
    Tokenizer tokenizer;
    REQUIRE(tokenizer.readFileToString("../../../../../tests/sp/TokenizerTest/empty.txt") == "");
}
// ai-gen end

TEST_CASE("Tokenizer::splitLine", "[splitLine]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile2.txt";
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
    const size_t expectedLineNumber = 5;
    REQUIRE(actualOutput.size() == expectedLineNumber);
}

TEST_CASE("Tokenizer::tokenize", "[tokenize]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile1.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    std::string actualContent = Tokenizer::readFileToString(testFileName);

    auto actualOutput = Tokenizer::tokenize(actualContent);
    REQUIRE(actualOutput.size() == 4);
    REQUIRE(actualOutput[0].getTokenType() == LexicalTokenType::NAME);
    REQUIRE(actualOutput[1].getTokenType() == LexicalTokenType::OPERATOR_ASSIGN);
    REQUIRE(actualOutput[2].getTokenType() == LexicalTokenType::INTEGER);
    REQUIRE(actualOutput[3].getTokenType() == LexicalTokenType::SYMBOL_SEMICOLON);
}

// ai-gen start(gpt,1,e)
// prompt: https://platform.openai.com/playground?thread=thread_B0hJ2obSjkZeF7NDPIUidhBG
/*
TEST_CASE("Tokenizer throws runtime error for invalid syntax", "[tokenize]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile4.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    std::string actualContent = Tokenizer::readFileToString(testFileName);

    REQUIRE_THROWS_WITH(Tokenizer::tokenize(actualContent), "Error: Invalid SIMPLE syntax.");
}
*/
// ai-gen end