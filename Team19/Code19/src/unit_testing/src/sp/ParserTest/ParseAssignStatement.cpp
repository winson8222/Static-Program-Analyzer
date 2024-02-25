#include "catch.hpp"
#include "sp/Parser/SimpleParserFacade.h"
#include <filesystem>

TEST_CASE("Testing parseAssign with only one constant", "[parse][assign]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/AssignStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	SECTION("Testing tree root node") {
		std::shared_ptr<ASTNode> tree_ptr = parser.parse();
		std::shared_ptr<ASTNode> assignStatement = (((tree_ptr->children)[0]->children)[0]->children)[0];

		REQUIRE(assignStatement->type == ASTNodeType::ASSIGN);
		REQUIRE(assignStatement->lineNumber == 1);
		REQUIRE(assignStatement->value == ASTUtility::getASTNodeType(ASTNodeType::ASSIGN));

		SECTION("Testing tree child node") {
			const auto& children = assignStatement->children;
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 1);
			REQUIRE(children[0]->value == "x");

			REQUIRE(children[1]->type == ASTNodeType::CONSTANT);
			REQUIRE(children[1]->lineNumber == 1);
			REQUIRE(children[1]->value == "1");
		}
	}
}

TEST_CASE("Testing parseAssign with an expression", "[parse][assign]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/AssignStmt2.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	SECTION("Testing tree root node") {
		std::shared_ptr<ASTNode> tree_ptr = parser.parse();
		std::shared_ptr<ASTNode> assignStatement = (((tree_ptr->children)[0]->children)[0]->children)[0];

		REQUIRE(assignStatement->type == ASTNodeType::ASSIGN);
		REQUIRE(assignStatement->lineNumber == 1);
		REQUIRE(assignStatement->value == ASTUtility::getASTNodeType(ASTNodeType::ASSIGN));

		SECTION("Testing tree child node") {
			const auto& children = assignStatement->children;
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 1);
			REQUIRE(children[0]->value == "read");

			REQUIRE(children[1]->type == ASTNodeType::ADD);
			REQUIRE(children[1]->lineNumber == 1);
			REQUIRE(children[1]->value == ASTUtility::getASTNodeType(ASTNodeType::ADD));

			SECTION("Testing expression of children") {
				const auto& constants = children[1]->children;
				REQUIRE(constants.size() == 2);
				REQUIRE(constants[0]->type == ASTNodeType::CONSTANT);
				REQUIRE(constants[0]->lineNumber == 1);
				REQUIRE(constants[0]->value == "1");

				REQUIRE(constants[1]->type == ASTNodeType::CONSTANT);
				REQUIRE(constants[1]->lineNumber == 1);
				REQUIRE(constants[1]->value == "3");
			}

		}
	}
}
