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
	REQUIRE(procedures[1]->value == "proc2");
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

TEST_CASE("Calling parseProgram for complex procedure", "[parse][program]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program3.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	auto& procedure = (tree_ptr->children)[0];

	// Checking procedure node
	REQUIRE(procedure->type == ASTNodeType::PROCEDURE);
	REQUIRE(procedure->value == "computeCentroid");

	auto statements = (procedure->children)[0]->children;

	// Check the statements of the parsed code
	REQUIRE(statements.size() == 6);

	auto firstStmt = statements[0];

	// Check the first statement
	REQUIRE(firstStmt->type == ASTNodeType::ASSIGN);
	auto firstStmtChildren = firstStmt->children;
	REQUIRE(firstStmtChildren.size() == 2);
	REQUIRE(firstStmtChildren[0]->type == ASTNodeType::VARIABLE);
	REQUIRE(firstStmtChildren[0]->value == "count");
	REQUIRE(firstStmtChildren[1]->type == ASTNodeType::CONSTANT);
	REQUIRE(firstStmtChildren[1]->value == "0");

}

TEST_CASE("Calling parseProgram for while procedures", "[parse][program]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program4.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->lineNumber == 1);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::PROGRAMS));


	std::shared_ptr<ASTNode> whileStatement = (((tree_ptr->children)[0]->children)[0]->children)[0];
	REQUIRE(whileStatement->type == ASTNodeType::WHILE);

	auto& whileChildren = whileStatement->children;
	REQUIRE(whileChildren.size() == 2);

	REQUIRE(whileChildren[0]->type == ASTNodeType::GREATER);
	REQUIRE(whileChildren[1]->type == ASTNodeType::STATEMENT_LIST);
}


TEST_CASE("Test string representations of programs", "[parse][program]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	std::string content;

	REQUIRE_NOTHROW(content = tree_ptr->toString());

	std::string subcontent1 = "  Type: Procedure, Line Number: 1, Value: proc1\n";
	std::string subcontent2 = "  Type: Procedure, Line Number: 5, Value: proc2\n";
	std::string subcontent3 = "  Type: Procedure, Line Number: 9, Value: proc3\n";

	REQUIRE(content.find(subcontent1) != std::string::npos);
	REQUIRE(content.find(subcontent2) != std::string::npos);
	REQUIRE(content.find(subcontent3) != std::string::npos);
}
