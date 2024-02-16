#include "catch.hpp"
#include "sp/Parser/SimpleParser.h"
#include <iostream>
#include <filesystem>

TEST_CASE("Program parsing throws an error for missing curly brace", "[parseProgram]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parseProcedure(), std::runtime_error);
}


TEST_CASE("Program parsing throws an error for missing curly braces", "[parseProgram]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure_Invalid2.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parseProcedure(), std::runtime_error);
}

TEST_CASE("Calling parseProgram with print, read, call statements", "[parseProgram]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parseProgram();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->lineNumber == 1);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::PROGRAMS));


	const auto procedure = (tree_ptr->children)[0];
	REQUIRE(procedure->type == ASTNodeType::PROCEDURE);
	REQUIRE(procedure->lineNumber == 1);
	REQUIRE(procedure->value == Utility::getASTNodeType(ASTNodeType::PROCEDURE));


	SECTION("Testing child nodes") {
		const auto& statementList = (procedure->children)[0];

		REQUIRE(statementList->type == ASTNodeType::STATEMENT_LIST);
		REQUIRE(statementList->lineNumber == 1);
		REQUIRE(statementList->value == Utility::getASTNodeType(ASTNodeType::STATEMENT_LIST));

		SECTION("Testing Print child node") {
			const auto& statements = statementList->children;
			REQUIRE(statements.size() == 3);

			auto callStatement = statements[0];
			REQUIRE(callStatement->type == ASTNodeType::CALL);
			REQUIRE(callStatement->lineNumber == 2);
			REQUIRE(callStatement->value == Utility::getASTNodeType(ASTNodeType::CALL));

			auto printStatement = statements[1];
			REQUIRE(printStatement->type == ASTNodeType::PRINT);
			REQUIRE(printStatement->lineNumber == 3);
			REQUIRE(printStatement->value == Utility::getASTNodeType(ASTNodeType::PRINT));

			auto readStatement = statements[2];
			REQUIRE(readStatement->type == ASTNodeType::READ);
			REQUIRE(readStatement->lineNumber == 4);
			REQUIRE(readStatement->value == Utility::getASTNodeType(ASTNodeType::READ));
		}
	}
}

TEST_CASE("Calling parseProgram for multiple procedures", "[parseProgram]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parseProgram();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->lineNumber == 1);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::PROGRAMS));


	const auto& procedures = tree_ptr->children;
	REQUIRE(procedures.size() == 3);

	REQUIRE(procedures[1]->type == ASTNodeType::PROCEDURE);
	REQUIRE(procedures[1]->value == Utility::getASTNodeType(ASTNodeType::PROCEDURE));
}

TEST_CASE("Test string representations of programs", "[parseProcedure]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParser parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parseProgram();


	std::string content;

	REQUIRE_NOTHROW(content = tree_ptr->toString());

	std::cout << content << std::endl;

	std::string subcontent1 = "  Type: Procedure, Line Number: 1, Value: Procedure\n";
	std::string subcontent2 = "  Type: Procedure, Line Number: 5, Value: Procedure\n";
	std::string subcontent3 = "  Type: Procedure, Line Number: 9, Value: Procedure\n";

	REQUIRE(content.find(subcontent1) != std::string::npos);
	REQUIRE(content.find(subcontent2) != std::string::npos);
	REQUIRE(content.find(subcontent3) != std::string::npos);

}