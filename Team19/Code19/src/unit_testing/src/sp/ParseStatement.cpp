#include "catch.hpp"
#include "sp/Parser/SimpleParser.h"
#include <filesystem>

TEST_CASE("Statement parsing throws an error with invalid syntax", "[parseStmt]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/InvalidStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parseStmt(), std::runtime_error);
}

TEST_CASE("Calling parsePrint from parseStmt", "[parseStmt]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/PrintStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parseStmt();

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

TEST_CASE("Calling parseRead from parseStmt", "[parseStmt]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/ReadStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	SECTION("Testing tree root node") {
		std::shared_ptr<ASTNode> tree_ptr = parser.parseStmt();

		REQUIRE(tree_ptr->type == ASTNodeType::READ);
		REQUIRE(tree_ptr->lineNumber == 1);
		REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::READ));

		SECTION("Testing tree child node") {
			const auto& children = tree_ptr->children;
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 1);
			REQUIRE(children[0]->value == "readableVariable");
		}
	}
}

TEST_CASE("Calling parseCall from parseStmt", "[parseStmt]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/CallStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	SECTION("Testing tree root node") {
		std::shared_ptr<ASTNode> tree_ptr = parser.parseStmt();

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