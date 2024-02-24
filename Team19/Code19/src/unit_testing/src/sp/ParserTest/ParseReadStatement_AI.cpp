#include "catch.hpp"
#include "sp/Parser/SimpleParserFacade.h"
#include <filesystem>

// ai-gen start(gpt, 2, e)
// Prompt: https://platform.openai.com/playground/p/CRO1bXNAQZB3Adua8DmfPuWb?model=gpt-4&mode=chat
TEST_CASE("Testing ReadStmt::buildTree()", "[parse][read]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/ReadStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	SECTION("Testing tree root node") {
		std::shared_ptr<ASTNode> tree_ptr = parser.parse();
		std::shared_ptr<ASTNode> readStatement = (((tree_ptr->children)[0]->children)[0]->children)[0];

		REQUIRE(readStatement->type == ASTNodeType::READ);
		REQUIRE(readStatement->lineNumber == 1);
		REQUIRE(readStatement->value == Utility::getASTNodeType(ASTNodeType::READ));

		SECTION("Testing tree child node") {
			const auto& children = readStatement->children;
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 1);
			REQUIRE(children[0]->value == "readableVariable");
		}
	}
}

TEST_CASE("Testing ReadStmt::buildTree() with read as variable", "[parse][read]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/ReadStmt2.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	SECTION("Testing tree root node") {
		std::shared_ptr<ASTNode> tree_ptr = parser.parse();
		std::shared_ptr<ASTNode> readStatement = (((tree_ptr->children)[0]->children)[0]->children)[0];

		REQUIRE(readStatement->type == ASTNodeType::READ);
		REQUIRE(readStatement->lineNumber == 1);
		REQUIRE(readStatement->value == Utility::getASTNodeType(ASTNodeType::READ));

		SECTION("Testing tree child node") {
			const auto& children = readStatement->children;
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 1);
			REQUIRE(children[0]->value == "read");
		}
	}
}
