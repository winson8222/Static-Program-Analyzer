#include "catch.hpp"
#include "sp/Parser/SimpleParserFacade.h"
#include <iostream>
#include <filesystem>

TEST_CASE("Procedure parsing throws an error for missing closing curly brace", "[parse][procedure]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure_Invalid1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Procedure parsing throws an error for missing curly braces", "[parse][procedure]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure_Invalid2.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}


TEST_CASE("Calling parseProcedure with print, read, call statements", "[parse][procedure]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->lineNumber == -1);
	REQUIRE(tree_ptr->value == ASTUtility::getASTNodeType(ASTNodeType::PROGRAMS));


	const auto procedure = (tree_ptr->children)[0];
	REQUIRE(procedure->type == ASTNodeType::PROCEDURE);
	REQUIRE(procedure->lineNumber == 0);
	REQUIRE(procedure->value == "procName");


	SECTION("Testing child nodes") {
		const auto& statementList = (procedure->children)[0];

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
}

TEST_CASE("Test string representations of procedures", "[parse][procedure]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	std::shared_ptr<ASTNode> procedure = (tree_ptr->children)[0];

	REQUIRE(procedure->type == ASTNodeType::PROCEDURE);
	REQUIRE(procedure->lineNumber == 0);
	REQUIRE(procedure->value == "procName");
}