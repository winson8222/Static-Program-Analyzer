#include "catch.hpp"
#include "sp/Parser/SimpleParser.h"
#include "sp/Parser/CallStmt.h"

// ai-gen start(gpt,1,e)
// Prompt: https://platform.openai.com/playground/p/BL0U9QBHRxSO8JyQGo0KpEUZ?mode=chat
TEST_CASE("CallStmt parsing is working correctly for valid input", "[SimpleParser::parseCall]") {
    std::ofstream testfile;
    testfile.open("test.txt");
    testfile << "call proc;\n";
    testfile.close();

    SimpleParser parser("test.txt");

    // Assuming parser.parseProgram() initiates a parse of the text file.
    parser.parseCall(0);

    // Assuming parser has a method to get CallStmt from parser, getCallStmt() 
    // which returns the last parsed CallStmt.
    CallStmt lastStmt = parser.getCallStmt();

    REQUIRE(lastStmt.getStartLine() == 1);
    REQUIRE(lastStmt.getEndLine() == 1); // Assuming your logic considers start and end line as similar for CallStmt.
}


TEST_CASE("CallStmt parsing throws an error with invalid syntax", "[SimpleParser]") {
    std::ofstream testfile;
    testfile.open("test.txt");
    testfile << "call42 proc;\n";
    testfile.close();

    SimpleParser parser("test.txt");

    // For this test, we expect parsing to terminate due to erroneous input.
    CHECK_THROWS_AS(parser.parseCall(0), std::runtime_error);
}
// ai-gen end