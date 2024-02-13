#include "catch.hpp"
#include "sp/Parser/SimpleParser.h"
#include <iostream>
#include <filesystem>

TEST_CASE("Procedure parsing throws an error for missing closing curly brace", "[parseProcedure]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure_Invalid1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parseProcedure(), std::runtime_error);
}


TEST_CASE("Procedure parsing throws an error for missing curly braces", "[parseProcedure]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure_Invalid2.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parseProcedure(), std::runtime_error);
}

TEST_CASE("Calling parseProcedure with print, read, call statements", "[parseProcedure]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parseProcedure();

	REQUIRE(tree_ptr->type == ASTNodeType::PROCEDURE);
	REQUIRE(tree_ptr->lineNumber == 1);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::PROCEDURE));

	SECTION("Testing child nodes") {
		const auto& statementList = (tree_ptr->children)[0];


		REQUIRE(statementList->type == ASTNodeType::STATEMENT_LIST);
		REQUIRE(statementList->lineNumber == 1);
		REQUIRE(statementList->value == Utility::getASTNodeType(ASTNodeType::STATEMENT_LIST));

		SECTION("Testing Print child node") {
			const auto& statements = statementList->children;
			REQUIRE(statements.size() == 3);

			auto& callStatement = statements[0];
			REQUIRE(callStatement->type == ASTNodeType::CALL);
			REQUIRE(callStatement->lineNumber == 2);
			REQUIRE(callStatement->value == Utility::getASTNodeType(ASTNodeType::CALL));

			auto& printStatement = statements[1];
			REQUIRE(printStatement->type == ASTNodeType::PRINT);
			REQUIRE(printStatement->lineNumber == 3);
			REQUIRE(printStatement->value == Utility::getASTNodeType(ASTNodeType::PRINT));

			auto& readStatement = statements[2];
			REQUIRE(readStatement->type == ASTNodeType::READ);
			REQUIRE(readStatement->lineNumber == 4);
			REQUIRE(readStatement->value == Utility::getASTNodeType(ASTNodeType::READ));
		}
	}
}

TEST_CASE("Test string representations of procedures", "[parseProcedure]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parseProcedure();

	REQUIRE(tree_ptr->type == ASTNodeType::PROCEDURE);
	REQUIRE(tree_ptr->lineNumber == 1);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::PROCEDURE));

	std::cout << "\nPRINT START\n" << std::endl;

	std::string content;

	REQUIRE_NOTHROW(content = tree_ptr->toString());

	std::string subcontent1 = "    Type: Call, Line Number: 2, Value: Call\n";
	REQUIRE(content.find(subcontent1) != std::string::npos);

	std::string subcontent2 = "  Type: StatementList, Line Number: 1, Value: StatementList\n";
	REQUIRE(content.find(subcontent2) != std::string::npos);

	std::string subcontent3 = "Type: Procedure, Line Number: 1, Value: Procedure\n";
	REQUIRE(content.find(subcontent3) != std::string::npos);

	std::cout << "\nPRINT END\n" << std::endl;
}