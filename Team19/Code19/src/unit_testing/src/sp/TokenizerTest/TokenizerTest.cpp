#include "sp/SPTokenizer/SPTokenizer.h"
#include "sp/SPTokenizer/FileProcessor.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

TEST_CASE("Tokenizer::readFileToString", "[readFileToString]") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "x = 1;";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    const std::string testFileContent = "x = 1;";

    std::string actualContent;
    REQUIRE_NOTHROW(actualContent = FileProcessor::readFileToString(filename));
    REQUIRE(actualContent == testFileContent);

    SPTokenizer::tokenize(actualContent);
    std::filesystem::remove(filename);
}

TEST_CASE("Test reading non-existent file", "[readFileToString]") {
    REQUIRE_THROWS_WITH(FileProcessor::readFileToString("non_existent_file.txt"),
        "Error: File either does not exist, or is corrupted!");
}

TEST_CASE("Test reading from an empty file", "[readFileToString]") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    REQUIRE(FileProcessor::readFileToString(filename) == "");
    std::filesystem::remove(filename);
}

TEST_CASE("Tokenize simple file without keywords", "[tokenize]") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "x = 1;";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    std::string actualContent = FileProcessor::readFileToString(filename);

    auto actualOutput = *(SPTokenizer::tokenize(actualContent));
    REQUIRE(actualOutput.size() == 4);
    REQUIRE(actualOutput[0].getTokenType() == LexicalTokenType::NAME);
    REQUIRE(actualOutput[1].getTokenType() == LexicalTokenType::OPERATOR_ASSIGN);
    REQUIRE(actualOutput[2].getTokenType() == LexicalTokenType::INTEGER);
    REQUIRE(actualOutput[3].getTokenType() == LexicalTokenType::SYMBOL_SEMICOLON);
    std::filesystem::remove(filename);
}


TEST_CASE("Check operator tokenizations", "[tokenize]") {
    std::string actualContent = "==!=<><=>=";

    auto actualOutput = *(SPTokenizer::tokenize(actualContent));
    REQUIRE(actualOutput.size() == 6);
    REQUIRE(actualOutput[0].getTokenType() == LexicalTokenType::OPERATOR_IS_EQUAL);
    REQUIRE(actualOutput[1].getTokenType() == LexicalTokenType::OPERATOR_NOT_EQUAL);
    REQUIRE(actualOutput[2].getTokenType() == LexicalTokenType::OPERATOR_LESS);
    REQUIRE(actualOutput[3].getTokenType() == LexicalTokenType::OPERATOR_GREATER);
    REQUIRE(actualOutput[4].getTokenType() == LexicalTokenType::OPERATOR_LESS_EQUAL);
    REQUIRE(actualOutput[5].getTokenType() == LexicalTokenType::OPERATOR_GREATER_EQUAL);
}

TEST_CASE("Tokenizer throws runtime error for invalid syntax", "[tokenize]") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "000abc = 10+e;";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    std::string actualContent = FileProcessor::readFileToString(filename);
    REQUIRE_THROWS_WITH(SPTokenizer::tokenize(actualContent), "Error: Invalid SIMPLE syntax.");
    std::filesystem::remove(filename);
}
