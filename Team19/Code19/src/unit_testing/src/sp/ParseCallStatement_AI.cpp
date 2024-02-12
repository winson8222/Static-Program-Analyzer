#include "catch.hpp"
#include "sp/Parser/SimpleParser.h"
#include <filesystem>
// ai-gen start(gpt,2,e)
// Prompt: https://platform.openai.com/playground/p/BL0U9QBHRxSO8JyQGo0KpEUZ?mode=chat
TEST_CASE("CallStmt parsing throws an error with invalid syntax", "[SimpleParser]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/InvalidStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parseCall(), std::runtime_error);
}
// ai-gen end

// ai-gen start(gpt, 2, e)
// Prompt: https://platform.openai.com/playground/p/CRO1bXNAQZB3Adua8DmfPuWb?model=gpt-4&mode=chat
TEST_CASE("Testing CallStmt::buildTree()", "[CallStmt]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/CallStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	SECTION("Testing tree root node") {
		std::shared_ptr<ASTNode> tree_ptr = parser.parseCall();

		REQUIRE(tree_ptr->type == ASTNodeType::CALL);
		REQUIRE(tree_ptr->lineNumber == 1);
		REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::CALL));

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
