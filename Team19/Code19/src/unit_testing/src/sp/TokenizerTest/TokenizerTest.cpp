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

TEST_CASE("Tokenizer::splitLine", "[splitLine]") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure procedure {"
                                "   x = 1;"
                                "   read y12;"
                                "   call abc;"
                                "   if (x > y) then {"
                                "  z = x - y;"
                                "   } else {"
                                "  z = y - x;"
                                "   }"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));

    const std::vector<std::string> expectedOutput = {
        "procedure testproc {",
        "   x = 1;",
        "   y = 2;",
        "   z = x + y;",
        "}"
    };

    std::string actualContent = FileProcessor::readFileToString(filename);
    std::vector<std::string> actualOutput = SPTokenizer::splitLine(actualContent);
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

    auto actualOutput = SPTokenizer::tokenize(actualContent);
    REQUIRE(actualOutput.size() == 4);
    REQUIRE(actualOutput[0].getTokenType() == LexicalTokenType::NAME);
    REQUIRE(actualOutput[1].getTokenType() == LexicalTokenType::OPERATOR_ASSIGN);
    REQUIRE(actualOutput[2].getTokenType() == LexicalTokenType::INTEGER);
    REQUIRE(actualOutput[3].getTokenType() == LexicalTokenType::SYMBOL_SEMICOLON);
    std::filesystem::remove(filename);
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


// IMPORTANT: When Tokenizer is able to check syntax, e.g. assigning the 2nd 'procedure' to NAME in procedure procedure, this will not work.
/*
TEST_CASE("Tokenize file with keywords", "[tokenize]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile4.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    std::string actualContent = FileProcessor::readFileToString(testFileName);

    auto actualOutput = SPTokenizer::tokenize(actualContent);
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

* FUTURE TEST CASES THAT ARE TO BE ADDRESSED.
TEST_CASE("Tokenizer throws runtime error for invalid syntax", "[tokenize]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/invalid1.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    std::string actualContent = Tokenizer::readFileToString(testFileName);

    REQUIRE_THROWS_WITH(Tokenizer::tokenize(actualContent), "Error: Invalid SIMPLE syntax.");
}
*/


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