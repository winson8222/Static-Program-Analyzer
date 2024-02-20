#include "catch.hpp"
#include "sp/Parser/SimpleParserFacade.h"
#include <iostream>
#include <filesystem>

TEST_CASE("Program parsing throws an error for missing curly brace", "[parse][program]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}


TEST_CASE("Calling parseProgram for multiple procedures", "[parse][program]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->lineNumber == 1);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::PROGRAMS));


	const auto& procedures = tree_ptr->children;
	REQUIRE(procedures.size() == 3);

	REQUIRE(procedures[1]->type == ASTNodeType::PROCEDURE);
	REQUIRE(procedures[1]->value == Utility::getASTNodeType(ASTNodeType::PROCEDURE));
}

TEST_CASE("Calling parseProgram for if-else-then procedures", "[parse][program]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program2.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->lineNumber == 1);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::PROGRAMS));


	std::shared_ptr<ASTNode> ifStatement = (((tree_ptr->children)[0]->children)[0]->children)[0];
	REQUIRE(ifStatement->type == ASTNodeType::IF_ELSE_THEN);

	auto& ifChildren = ifStatement->children;
	REQUIRE(ifChildren.size() == 3);

	REQUIRE(ifChildren[0]->type == ASTNodeType::GREATER);
	REQUIRE(ifChildren[1]->type == ASTNodeType::STATEMENT_LIST);
	REQUIRE(ifChildren[2]->type == ASTNodeType::STATEMENT_LIST);
}

TEST_CASE("Test string representations of programs", "[parse][program]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

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

TEST_CASE("Test complete string representations of programs", "[parse][program]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program3.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
}