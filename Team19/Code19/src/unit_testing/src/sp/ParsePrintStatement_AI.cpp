#include "catch.hpp"
#include "sp/Parser/SimpleParser.h"
#include <filesystem>
// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/BL0U9QBHRxSO8JyQGo0KpEUZ?mode=chat
TEST_CASE("PrintStmt parsing is working correctly for valid input", "[SimpleParser::parsePrint]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/PrintStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	PrintStmt lastStmt = parser.parsePrint();

	// Assuming parser has a method to get PrintStmt from parser, getPrintStmt() 
	// which returns the last parsed PrintStmt.

	REQUIRE(lastStmt.getStartLine() == 1);
	REQUIRE(lastStmt.getEndLine() == 1); // Assuming your logic considers start and end line as similar for PrintStmt.
}


TEST_CASE("PrintStmt parsing throws an error with invalid syntax", "[SimpleParser]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/CallStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parsePrint(), std::runtime_error);
}
// ai-gen end

// ai-gen start(gpt, 2, e)
// Prompt: https://platform.openai.com/playground/p/CRO1bXNAQZB3Adua8DmfPuWb?model=gpt-4&mode=chat
TEST_CASE("Testing PrintStmt::buildTree()", "[PrintStmt]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/PrintStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	PrintStmt printStmt = parser.parsePrint();

	SECTION("Testing tree root node") {
		std::shared_ptr<ASTNode> tree_ptr = printStmt.buildTree();

		REQUIRE(tree_ptr->type == ASTNodeType::PRINT);
		REQUIRE(tree_ptr->lineNumber == 1);
		REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::PRINT));

		SECTION("Testing tree child node") {
			const auto& children = tree_ptr->children;
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 1);
			REQUIRE(children[0]->value == "x");
		}
	}
}
// ai-gen end
