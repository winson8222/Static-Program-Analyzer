#include "catch.hpp"
#include "sp/Parser/SimpleParser.h"
#include <filesystem>

TEST_CASE("StatementList parsing throws an error with invalid syntax", "[parseStmtLst]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Stmt_Invalid1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parseStmt(), std::runtime_error);
}

TEST_CASE("Calling parsePrint from parseStmtLst", "[parseStmtLst]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/StmtList1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parseStmtLst();

	REQUIRE(tree_ptr->type == ASTNodeType::STATEMENT_LIST);
	REQUIRE(tree_ptr->lineNumber == 1);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::STATEMENT_LIST));

	SECTION("Testing Print child node") {
		const auto& statements = tree_ptr->children;
		REQUIRE(statements.size() == 1);

		auto printStatement = statements[0];
		REQUIRE(printStatement->type == ASTNodeType::PRINT);
		REQUIRE(printStatement->lineNumber == 1);
		REQUIRE(printStatement->value == Utility::getASTNodeType(ASTNodeType::PRINT));

		SECTION("Testing Variable child node") {
			const auto& variable = printStatement->children;
			REQUIRE(variable.size() == 1);
			REQUIRE(variable[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(variable[0]->lineNumber == 1);
			REQUIRE(variable[0]->value == "x");
		}
	}
}

TEST_CASE("Calling multiple parseStmt from parseStmtLst", "[parseStmtLst]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/StmtList2.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parseStmtLst();

	REQUIRE(tree_ptr->type == ASTNodeType::STATEMENT_LIST);
	REQUIRE(tree_ptr->lineNumber == 1);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::STATEMENT_LIST));

	SECTION("Testing Print child node") {
		const auto& statements = tree_ptr->children;
		REQUIRE(statements.size() == 3);

		auto callStatement = statements[0];
		REQUIRE(callStatement->type == ASTNodeType::CALL);
		REQUIRE(callStatement->lineNumber == 1);
		REQUIRE(callStatement->value == Utility::getASTNodeType(ASTNodeType::CALL));

		auto printStatement = statements[1];
		REQUIRE(printStatement->type == ASTNodeType::PRINT);
		REQUIRE(printStatement->lineNumber == 2);
		REQUIRE(printStatement->value == Utility::getASTNodeType(ASTNodeType::PRINT));

		auto readStatement = statements[2];
		REQUIRE(readStatement->type == ASTNodeType::READ);
		REQUIRE(readStatement->lineNumber == 3);
		REQUIRE(readStatement->value == Utility::getASTNodeType(ASTNodeType::READ));
	}
}
