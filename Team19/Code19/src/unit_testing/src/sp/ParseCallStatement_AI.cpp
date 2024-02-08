#include "catch.hpp"
#include "sp/Parser/SimpleParser.h"
#include <filesystem>
// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/BL0U9QBHRxSO8JyQGo0KpEUZ?mode=chat
TEST_CASE("CallStmt parsing is working correctly for valid input", "[SimpleParser::parseCall]") {
    const std::string testFileName = "../../../../../tests/sp/ParserTest/CallStmt1.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    SimpleParser parser(testFileName);

    CallStmt lastStmt = parser.parseCall(0);

    // Assuming parser has a method to get CallStmt from parser, getCallStmt() 
    // which returns the last parsed CallStmt.

    REQUIRE(lastStmt.getStartLine() == 1);
    REQUIRE(lastStmt.getEndLine() == 1); // Assuming your logic considers start and end line as similar for CallStmt.
}


TEST_CASE("CallStmt parsing throws an error with invalid syntax", "[SimpleParser]") {
    const std::string testFileName = "../../../../../tests/sp/ParserTest/CallStmt2.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    SimpleParser parser(testFileName);

    // For this test, we expect parsing to terminate due to erroneous input.
    CHECK_THROWS_AS(parser.parseCall(0), std::runtime_error);
}

// ai-gen end