#include "sp/SPTokenizer/SPTokenizer.h"
#include "sp/SPTokenizer/LexicalToken.h"
#include "sp/SPTokenizer/FileProcessor.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>
#include <regex>

TEST_CASE("Tokenizer::readFileToString", "[readFileToString]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile1.txt";
    const std::string testFileContent = "x = 1;";
    REQUIRE(std::filesystem::exists(testFileName));

    std::string actualContent;
    REQUIRE_NOTHROW(actualContent = FileProcessor::readFileToString(testFileName));
    REQUIRE(actualContent == testFileContent);

    SPTokenizer::tokenize(actualContent);
}

TEST_CASE("Test reading non-existent file", "[readFileToString]") {
    REQUIRE_THROWS_WITH(FileProcessor::readFileToString("non_existent_file.txt"),
        "Error: File either does not exist, or is corrupted!");
}

TEST_CASE("Test reading from an empty file", "[readFileToString]") {
    REQUIRE(FileProcessor::readFileToString("../../../../../tests/sp/TokenizerTest/empty.txt") == "");
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

    std::string actualContent = FileProcessor::readFileToString(testFileName);
    std::vector<std::string> actualOutput = SPTokenizer::splitLine(actualContent);
}

TEST_CASE("Tokenize simple file without keywords", "[tokenize]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile1.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    std::string actualContent = FileProcessor::readFileToString(testFileName);

    auto actualOutput = SPTokenizer::tokenize(actualContent);
    REQUIRE(actualOutput.size() == 4);
    REQUIRE(actualOutput[0].getTokenType() == LexicalTokenType::NAME);
    REQUIRE(actualOutput[1].getTokenType() == LexicalTokenType::OPERATOR_ASSIGN);
    REQUIRE(actualOutput[2].getTokenType() == LexicalTokenType::INTEGER);
    REQUIRE(actualOutput[3].getTokenType() == LexicalTokenType::SYMBOL_SEMICOLON);
}


TEST_CASE("Check operator tokenizations", "[tokenize]") {
    std::string actualContent = "==!=<><=>=";

    auto actualOutput = SPTokenizer::tokenize(actualContent);
    REQUIRE(actualOutput.size() == 6);
    REQUIRE(actualOutput[0].getTokenType() == LexicalTokenType::OPERATOR_IS_EQUAL);
    REQUIRE(actualOutput[1].getTokenType() == LexicalTokenType::OPERATOR_NOT_EQUAL);
    REQUIRE(actualOutput[2].getTokenType() == LexicalTokenType::OPERATOR_LESS);
    REQUIRE(actualOutput[3].getTokenType() == LexicalTokenType::OPERATOR_GREATER);
    REQUIRE(actualOutput[4].getTokenType() == LexicalTokenType::OPERATOR_LESS_EQUAL);
    REQUIRE(actualOutput[5].getTokenType() == LexicalTokenType::OPERATOR_GREATER_EQUAL);
}

TEST_CASE("Tokenizer throws runtime error for invalid syntax", "[tokenize]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile5.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    std::string actualContent = FileProcessor::readFileToString(testFileName);
    REQUIRE_THROWS_WITH(SPTokenizer::tokenize(actualContent), "Error: Invalid SIMPLE syntax.");
}