#include "catch.hpp"
#include "sp/Parser/SimpleParserFacade.h"
#include <filesystem>


// ai-gen start(gpt, 2, e)
// Prompt: https://platform.openai.com/playground/p/CRO1bXNAQZB3Adua8DmfPuWb?model=gpt-4&mode=chat
TEST_CASE("Testing PrintStmt::buildTree()", "[parse][print]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/PrintStmt1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();
	std::shared_ptr<ASTNode> printStatement = (((tree_ptr->children)[0]->children)[0]->children)[0];


	REQUIRE(printStatement->type == ASTNodeType::PRINT);
	REQUIRE(printStatement->lineNumber == 2);
	REQUIRE(printStatement->value == Utility::getASTNodeType(ASTNodeType::PRINT));

	SECTION("Testing tree child node") {
		const auto& children = printStatement->children;
		REQUIRE(children.size() == 1);
		REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
		REQUIRE(children[0]->lineNumber == 2);
		REQUIRE(children[0]->value == "read");
	}
}
// ai-gen end
