/*
#include "catch.hpp"
#include "sp/Parser/SimpleParser.h"
#include <filesystem>

TEST_CASE("AssignStmt parsing throws an error with invalid syntax", "[AssignStmt]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/CallStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parseAssign(), std::runtime_error);
}

TEST_CASE("Testing AssignStmt::buildTree()", "[AssignStmt]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/AssignStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	SECTION("Testing tree root node") {
		std::shared_ptr<ASTNode> tree_ptr = parser.parseAssign();

		REQUIRE(tree_ptr->type == ASTNodeType::ASSIGN);
		REQUIRE(tree_ptr->lineNumber == 1);
		REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::ASSIGN));

		SECTION("Testing tree child node") {
			const auto& children = tree_ptr->children;
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 1);
			REQUIRE(children[0]->value == "x");

			REQUIRE(children[1]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[1]->lineNumber == 1);
			REQUIRE(children[1]->value == "1");
		}
	}
}
*/