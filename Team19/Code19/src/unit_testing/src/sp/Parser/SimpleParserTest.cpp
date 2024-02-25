#include "catch.hpp"
#include "sp/Parser/SimpleParserFacade.h"
#include <iostream>
#include <filesystem>

TEST_CASE("Program parsing throws an error for missing curly brace after procedure end.") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Program parsing throws an error for missing closing curly brace.") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid2.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Program parsing throws an error for missing curly braces.") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid3.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Program parsing throws an error for extra variable in print statement") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid4.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Program parsing throws an error for missing parenthesis around !(cond_expr) with following && operator.") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid5.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Program parsing throws an error for extra parenthesis around cond_expr.") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid6.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Program parsing throws an error for invalid procedure name containing special symbols.") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid7.txt";
	REQUIRE(std::filesystem::exists(testFileName));


	//CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Program parsing throws an error for invalid procedure name starting with numbers.") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid8.txt";
	REQUIRE(std::filesystem::exists(testFileName));


	//CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}

TEST_CASE("Program parsing throws an error for invalid keyword.") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program_Invalid9.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);

	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
}



TEST_CASE("Single procedure, with read statement") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->value == ASTUtility::getASTNodeType(ASTNodeType::PROGRAMS));


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

	REQUIRE(statements.size() == 13);

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
	REQUIRE(tree_ptr->value == ASTUtility::getASTNodeType(ASTNodeType::PROGRAMS));

	REQUIRE(tree_ptr->children.size() == 30);
}

TEST_CASE("Parsing single program with all possible statements types.") {
	const std::string testFileName = "../../../../../tests/sp/ParserTest/Program4.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	auto& statements = (((tree_ptr->children)[0]->children)[0]->children);
	REQUIRE(statements.size() == 6);

	SECTION("Testing While Statement") {
		std::shared_ptr<ASTNode> whileStatement = statements[0];
		REQUIRE(whileStatement->type == ASTNodeType::WHILE);
		REQUIRE(whileStatement->lineNumber == 1);
		REQUIRE(whileStatement->value == ASTUtility::getASTNodeType(ASTNodeType::WHILE));

		auto& whileChildren = whileStatement->children;
		REQUIRE(whileChildren.size() == 2);

		SECTION("Testing predicates tree child node") {
			REQUIRE(whileChildren[0]->type == ASTNodeType::NOT);

			auto& cond_expr = (whileChildren[0]->children)[0];

			REQUIRE(cond_expr->type == ASTNodeType::GREATER);
			REQUIRE(cond_expr->lineNumber == 1);
			REQUIRE(cond_expr->value == ASTUtility::getASTNodeType(ASTNodeType::GREATER));

			const auto& children = cond_expr->children;
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 1);
			REQUIRE(children[0]->value == "read");

			REQUIRE(children[1]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[1]->lineNumber == 1);
			REQUIRE(children[1]->value == "procedure");
		}

		SECTION("Testing Statement List tree child node") {
			REQUIRE(whileChildren[1]->type == ASTNodeType::STATEMENT_LIST);
			auto& statement = (whileChildren[1]->children)[0];

			REQUIRE(statement->type == ASTNodeType::ASSIGN);
			REQUIRE(statement->lineNumber == 2);
			REQUIRE(statement->value == ASTUtility::getASTNodeType(ASTNodeType::ASSIGN));

			const auto& children = statement->children;
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 2);
			REQUIRE(children[0]->value == "if");

			REQUIRE(children[1]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[1]->lineNumber == 2);
			REQUIRE(children[1]->value == "if");
		}
	}

	SECTION("Testing if-then-else statement") {
		auto& ifStatement = statements[1];

		REQUIRE(ifStatement->type == ASTNodeType::IF_ELSE_THEN);
		REQUIRE(ifStatement->lineNumber == 3);
		REQUIRE(ifStatement->value == ASTUtility::getASTNodeType(ASTNodeType::IF_ELSE_THEN));

		auto& ifChildren = ifStatement->children;
		REQUIRE(ifChildren.size() == 3);

		SECTION("Testing predicates tree child node") {
			auto& cond_expr = ifChildren[0];

			REQUIRE(cond_expr->type == ASTNodeType::LESSER);
			REQUIRE(cond_expr->lineNumber == 3);
			REQUIRE(cond_expr->value == ASTUtility::getASTNodeType(ASTNodeType::LESSER));

			const auto& children = cond_expr->children;
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 3);
			REQUIRE(children[0]->value == "then");

			REQUIRE(children[1]->type == ASTNodeType::CONSTANT);
			REQUIRE(children[1]->lineNumber == 3);
			REQUIRE(children[1]->value == "2");
		}

		SECTION("Testing If-then statement list node") {
			REQUIRE(ifChildren[1]->type == ASTNodeType::STATEMENT_LIST);
			auto& statement = (ifChildren[1]->children)[0];

			REQUIRE(statement->type == ASTNodeType::ASSIGN);
			REQUIRE(statement->lineNumber == 4);
			REQUIRE(statement->value == ASTUtility::getASTNodeType(ASTNodeType::ASSIGN));

			const auto& children = statement->children;
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 4);
			REQUIRE(children[0]->value == "else");

			REQUIRE(children[1]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[1]->lineNumber == 4);
			REQUIRE(children[1]->value == "else");
		}

		SECTION("Testing Else statement list node") {
			REQUIRE(ifChildren[1]->type == ASTNodeType::STATEMENT_LIST);
			auto& statement = (ifChildren[2]->children)[0];

			REQUIRE(statement->type == ASTNodeType::ASSIGN);
			REQUIRE(statement->lineNumber == 5);
			REQUIRE(statement->value == ASTUtility::getASTNodeType(ASTNodeType::ASSIGN));

			const auto& children = statement->children;
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 5);
			REQUIRE(children[0]->value == "while");

			REQUIRE(children[1]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[1]->lineNumber == 5);
			REQUIRE(children[1]->value == "then");
		}
	}

	SECTION("Testing assign statement") {
		auto& assignStatement = statements[2];

		REQUIRE(assignStatement->type == ASTNodeType::ASSIGN);
		REQUIRE(assignStatement->lineNumber == 6);
		REQUIRE(assignStatement->value == ASTUtility::getASTNodeType(ASTNodeType::ASSIGN));

		SECTION("Testing tree child node") {
			const auto& children = assignStatement->children;
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 6);
			REQUIRE(children[0]->value == "read");

			REQUIRE(children[1]->type == ASTNodeType::ADD);
			REQUIRE(children[1]->lineNumber == 6);
			REQUIRE(children[1]->value == ASTUtility::getASTNodeType(ASTNodeType::ADD));

			SECTION("Testing expression of children") {
				const auto& constants = children[1]->children;
				REQUIRE(constants.size() == 2);
				REQUIRE(constants[0]->type == ASTNodeType::CONSTANT);
				REQUIRE(constants[0]->lineNumber == 6);
				REQUIRE(constants[0]->value == "1");

				REQUIRE(constants[1]->type == ASTNodeType::VARIABLE);
				REQUIRE(constants[1]->lineNumber == 6);
				REQUIRE(constants[1]->value == "program");
			}
		}
	}

	SECTION("Testing call statement") {
		auto& callStatement = statements[3];
		REQUIRE(callStatement->type == ASTNodeType::CALL);
		REQUIRE(callStatement->lineNumber == 7);
		REQUIRE(callStatement->value == ASTUtility::getASTNodeType(ASTNodeType::CALL));

		SECTION("Testing tree child node") {
			const auto& children = callStatement->children;
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 7);
			REQUIRE(children[0]->value == "call");
		}
	}

	SECTION("Testing print statement") {
		auto& printStatement = statements[4];
		REQUIRE(printStatement->type == ASTNodeType::PRINT);
		REQUIRE(printStatement->lineNumber == 8);
		REQUIRE(printStatement->value == ASTUtility::getASTNodeType(ASTNodeType::PRINT));

		SECTION("Testing tree child node") {
			const auto& children = printStatement->children;
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 8);
			REQUIRE(children[0]->value == "read");
		}
	}

	SECTION("Testing read statement") {
		auto& readStatement = statements[5];
		REQUIRE(readStatement->type == ASTNodeType::READ);
		REQUIRE(readStatement->lineNumber == 9);
		REQUIRE(readStatement->value == ASTUtility::getASTNodeType(ASTNodeType::READ));

		SECTION("Testing tree child node") {
			const auto& children = readStatement->children;
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 9);
			REQUIRE(children[0]->value == "print");
		}
	}
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
