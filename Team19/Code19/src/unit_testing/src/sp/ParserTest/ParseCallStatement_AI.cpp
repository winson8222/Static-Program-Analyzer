#include "catch.hpp"
#include "sp/Parser/SimpleParserFacade.h"
#include <filesystem>

// ai-gen start(gpt, 2, e)
// Prompt: https://platform.openai.com/playground/p/CRO1bXNAQZB3Adua8DmfPuWb?model=gpt-4&mode=chat
TEST_CASE("Testing CallStmt::buildTree()", "[parse][call]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/CallStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	SECTION("Testing tree root node") {
		std::shared_ptr<ASTNode> tree_ptr = parser.parse();
		std::shared_ptr<ASTNode> callStatement = (((tree_ptr->children)[0]->children)[0]->children)[0];

		REQUIRE(callStatement->type == ASTNodeType::CALL);
		REQUIRE(callStatement->lineNumber == 1);
		REQUIRE(callStatement->value == Utility::getASTNodeType(ASTNodeType::CALL));

		SECTION("Testing tree child node") {
			const auto& children = callStatement->children;
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 1);
			REQUIRE(children[0]->value == "x");
		}
	}
}
// ai-gen end
