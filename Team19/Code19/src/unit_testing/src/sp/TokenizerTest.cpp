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

TEST_CASE("Test reading non-existent file", "[readFileToString]") {
    REQUIRE_THROWS_WITH(Tokenizer::readFileToString("non_existent_file.txt"),
        "Error: Unable to open the input file.");
}

TEST_CASE("Test reading from an empty file", "[readFileToString]") {
    REQUIRE(Tokenizer::readFileToString("../../../../../tests/sp/TokenizerTest/empty.txt") == "");
}

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

TEST_CASE("Tokenize simple file without keywords", "[tokenize]") {
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

// IMPORTANT: When Tokenizer is able to check syntax, e.g. assigning the 2nd 'procedure' to NAME in procedure procedure, this will not work.
TEST_CASE("Tokenize file with keywords", "[tokenize]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile4.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    std::string actualContent = Tokenizer::readFileToString(testFileName);

    auto actualOutput = Tokenizer::tokenize(actualContent);
    REQUIRE(actualOutput.size() == 9);
    REQUIRE(actualOutput[0].getTokenType() == LexicalTokenType::KEYWORD_IF);
    REQUIRE(actualOutput[1].getTokenType() == LexicalTokenType::KEYWORD_THEN);
    REQUIRE(actualOutput[2].getTokenType() == LexicalTokenType::KEYWORD_ELSE);
    REQUIRE(actualOutput[3].getTokenType() == LexicalTokenType::KEYWORD_READ);
    REQUIRE(actualOutput[4].getTokenType() == LexicalTokenType::KEYWORD_CALL);
    REQUIRE(actualOutput[5].getTokenType() == LexicalTokenType::KEYWORD_PRINT);
    REQUIRE(actualOutput[6].getTokenType() == LexicalTokenType::KEYWORD_WHILE);
    REQUIRE(actualOutput[7].getTokenType() == LexicalTokenType::KEYWORD_PROCEDURE);
    REQUIRE(actualOutput[8].getTokenType() == LexicalTokenType::NAME);
}

/*
* FUTURE TEST CASES THAT ARE TO BE ADDRESSED.
TEST_CASE("Tokenizer throws runtime error for invalid syntax", "[tokenize]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/invalid1.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    std::string actualContent = Tokenizer::readFileToString(testFileName);

    REQUIRE_THROWS_WITH(Tokenizer::tokenize(actualContent), "Error: Invalid SIMPLE syntax.");
}
*/