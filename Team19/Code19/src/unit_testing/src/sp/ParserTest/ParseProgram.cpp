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

TEST_CASE("Program parsing throws an error for missing parenthesis around !(cond_expr) with following && operator.", "[parse][program]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid2.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	// For this test, we expect parsing to terminate due to erroneous input.
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Single procedure, with read statement") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::PROGRAMS));


	const auto& procedures = tree_ptr->children;
	REQUIRE(procedures.size() == 1);

	REQUIRE(procedures[0]->type == ASTNodeType::PROCEDURE);
	REQUIRE(procedures[0]->value == "main");

	const auto& statement = ((procedures[0]->children)[0]->children)[0];
	REQUIRE(statement->type == ASTNodeType::READ);
	REQUIRE(statement->lineNumber == 1);
	REQUIRE(statement->children[0]->value == "helloWorld");
}

TEST_CASE("Single procedure, all possible conditional expressions in while statements") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program2.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();
	auto& procedure = (tree_ptr->children)[0];

	// Checking procedure node
	REQUIRE(procedure->type == ASTNodeType::PROCEDURE);
	REQUIRE(procedure->value == "conditionalExpressions");

	const auto& statements = (procedure->children)[0]->children;

	REQUIRE(statements.size() == 11);

	for (int i = 0; i < statements.size(); i++) {
		auto& statement = statements[i];
		REQUIRE(statement->type == ASTNodeType::WHILE);
		
		auto& contents = ((statement->children)[1]->children)[0];
		REQUIRE(contents->type == ASTNodeType::READ);
		REQUIRE((contents->children)[0]->value == "x");
	}
}

TEST_CASE("Multiple procedures, all names that may be potential keywords.") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program3.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->lineNumber == -1);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::PROGRAMS));

	REQUIRE(tree_ptr->children.size() == 30);
}

TEST_CASE("Calling parseProgram for if statement type procedure", "[parse][program]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program7.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->lineNumber == -1);
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
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program5.txt";
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

	auto lastStmt = statements[5];

	// Check the last statement
	REQUIRE(lastStmt->type == ASTNodeType::ASSIGN);
	auto& lastStmtChildren = lastStmt->children;
	REQUIRE(lastStmtChildren.size() == 2);
	REQUIRE(lastStmtChildren[0]->type == ASTNodeType::VARIABLE);
	REQUIRE(lastStmtChildren[0]->value == "normSq");
	REQUIRE(lastStmtChildren[1]->type == ASTNodeType::ADD);

	auto& additionValues = lastStmtChildren[1]->children;
	REQUIRE(additionValues.size() == 2);
	REQUIRE(additionValues[0]->type == ASTNodeType::MULTIPLY);
	REQUIRE(additionValues[1]->type == ASTNodeType::MULTIPLY);

	auto& firstExpr = additionValues[0]->children;
	REQUIRE(firstExpr.size() == 2);
	REQUIRE(firstExpr[0]->type == ASTNodeType::VARIABLE);
	REQUIRE(firstExpr[0]->value == "cenX");
	REQUIRE(firstExpr[1]->type == ASTNodeType::VARIABLE);
	REQUIRE(firstExpr[1]->value == "cenX");

	auto& lastExpr = additionValues[1]->children;
	REQUIRE(lastExpr.size() == 2);
	REQUIRE(lastExpr[0]->type == ASTNodeType::VARIABLE);
	REQUIRE(lastExpr[0]->value == "cenY");
	REQUIRE(lastExpr[1]->type == ASTNodeType::VARIABLE);
	REQUIRE(lastExpr[1]->value == "cenY");
}

TEST_CASE("Calling parseProgram for while procedures", "[parse][program]") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program4.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->lineNumber == -1);
	REQUIRE(tree_ptr->value == Utility::getASTNodeType(ASTNodeType::PROGRAMS));


	std::shared_ptr<ASTNode> whileStatement = (((tree_ptr->children)[0]->children)[0]->children)[0];
	REQUIRE(whileStatement->type == ASTNodeType::WHILE);

	auto& whileChildren = whileStatement->children;
	REQUIRE(whileChildren.size() == 2);

	REQUIRE(whileChildren[0]->type == ASTNodeType::NOT);
	REQUIRE(whileChildren[1]->type == ASTNodeType::STATEMENT_LIST);
}

TEST_CASE("sp/AST/ASTHelper") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program6.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();
}

TEST_CASE("Test string representations of programs", "[parse][program]") {
	// Generate test file
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	std::string content;

	REQUIRE_NOTHROW(content = tree_ptr->toString());
}
