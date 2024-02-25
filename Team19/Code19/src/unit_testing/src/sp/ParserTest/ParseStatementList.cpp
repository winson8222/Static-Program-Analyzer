#include "catch.hpp"
#include "sp/Parser/SimpleParserFacade.h"
#include <filesystem>

TEST_CASE("StatementList parsing throws an error with invalid syntax", "[parse][statementList]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/StmtList_Invalid1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Calling multiple statements", "[parse][statementList]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/StmtList1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();
	std::shared_ptr<ASTNode> statementList = ((tree_ptr->children)[0]->children)[0];

	REQUIRE(statementList->type == ASTNodeType::STATEMENT_LIST);
	REQUIRE(statementList->lineNumber == 0);
	REQUIRE(statementList->value == ASTUtility::getASTNodeType(ASTNodeType::STATEMENT_LIST));

	SECTION("Testing Print child node") {
		const auto& statements = statementList->children;
		REQUIRE(statements.size() == 3);

		auto callStatement = statements[0];
		REQUIRE(callStatement->type == ASTNodeType::CALL);
		REQUIRE(callStatement->lineNumber == 1);
		REQUIRE(callStatement->value == ASTUtility::getASTNodeType(ASTNodeType::CALL));

		auto printStatement = statements[1];
		REQUIRE(printStatement->type == ASTNodeType::PRINT);
		REQUIRE(printStatement->lineNumber == 2);
		REQUIRE(printStatement->value == ASTUtility::getASTNodeType(ASTNodeType::PRINT));

		auto readStatement = statements[2];
		REQUIRE(readStatement->type == ASTNodeType::READ);
		REQUIRE(readStatement->lineNumber == 3);
		REQUIRE(readStatement->value == ASTUtility::getASTNodeType(ASTNodeType::READ));
	}
}
