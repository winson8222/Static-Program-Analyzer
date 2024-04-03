#include "catch.hpp"
#include "sp/Parser/SimpleParserFacade.h"
#include <iostream>
#include <filesystem>
#include <fstream>
#include <utility>
#include <functional>
#include <string>
#include <vector>

TEST_CASE("Program parsing throws an error for missing curly brace after procedure end.") {
	std::string filename = "sample.txt";
	std::string sampleProgram =
		"procedure proc1 {"
		"	print x;"
		""
		"procedure proc2 "
		"	call y;"
		"}";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
	std::filesystem::remove(filename);
}

TEST_CASE("Program parsing throws an error for missing closing curly brace.") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure invalidProcedure { call y;";
	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
	std::filesystem::remove(filename);
}

TEST_CASE("Program parsing throws an error for missing curly braces.") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure invalidProcedure call y;";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
	std::filesystem::remove(filename);
}

TEST_CASE("Program parsing throws an error for extra variable in print statement") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure proc { print xyz call; }";
	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
	std::filesystem::remove(filename);
}

TEST_CASE("Program parsing throws an error for missing parenthesis around !(cond_expr)") {
	std::string filename = "sample.txt";
	std::string sampleProgram =
		"procedure procedure {"
		"	while (!(read != 11) && !(read == while)) {"
		"		print = 0;"
		"	}"
		"}";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
	std::filesystem::remove(filename);
}

TEST_CASE("Program parsing throws an error for extra parenthesis around cond_expr.") {
	std::string filename = "sample.txt";
	std::string sampleProgram =
		"procedure procedure {"
		"	while ((read != 11)) {"
		"		print = 0;"
		"	}"
		"}";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
	std::filesystem::remove(filename);
}

TEST_CASE("Program parsing throws an error for invalid keyword.") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure main { write x; }";
	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
	std::filesystem::remove(filename);
}

TEST_CASE("Program parsing throws an error for nested procedures.") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure main { procedure nested { write x; }}";
	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	CHECK_THROWS_AS(parser.parse(), std::runtime_error);
	std::filesystem::remove(filename);
}

TEST_CASE("Single procedure, with read statement") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure main { read helloWorld; }";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->getType() == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::PROGRAMS)->second);

	std::vector<std::shared_ptr<ASTNode>> procedures = tree_ptr->getChildren();
	REQUIRE(procedures.size() == 1);

	REQUIRE(procedures[0]->getType() == ASTNodeType::PROCEDURE);
	REQUIRE(procedures[0]->getValue() == "main");

	std::shared_ptr<ASTNode> statement = procedures[0]->getChildByIndex(0)->getChildByIndex(0);
	REQUIRE(statement->getType() == ASTNodeType::READ);
	REQUIRE(statement->getLineNumber() == 1);
	REQUIRE(statement->getChildByIndex(0)->getValue() == "helloWorld");
	std::filesystem::remove(filename);
}

TEST_CASE("Single procedure, all possible conditional expressions in while statements") {
	std::string filename = "sample.txt";
	std::string sampleProgram =
		"procedure conditionalExpressions {"
		"	while(x == 2) { read x; }"
		"	while(x != 2) { read x; }"
		"	while(x < 2) { read x; }"
		"	while(x <= 2) { read x; }"
		"	while(x > 2) { read x; }"
		"	while(x >= 2) { read x; }"
		"	while(!(x == 2)) { read x; }"
		"	while(0 == 2147483647) { read x; }"
		"	while(0 != 2147483647) { read x; }"
		"	while(0 < 2147483647) { read x; }"
		"	while(0 <= 2147483647) { read x; }"
		"	while(0 > 2147483647) { read x; }"
		"	while(0 >= 2147483647) { read x; }"
		"	while(!(0 == 2147483647)) { read x; }"
		"	while((x == 2) && (x == 1)) { read x; }"
		"	while((x != 2) || (x != 2)) { read x; }"
		"	while((!(x == 2)) && (!(x == 1))) { read x; }"
		"	while( ((x == 2) && (x == 1)) || (x == 3)) { read x; }"
		"	while(!(!(!(!(!(!(!(!(!(!(x==3))))))))))) { read x; }"
		"	while(((x <= y) || (!(y == z))) && (!(z >= x))) { read x; }"
		"}";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();
	std::shared_ptr<ASTNode> procedure = tree_ptr->getChildByIndex(0);

	// Checking procedure node
	REQUIRE(procedure->getType() == ASTNodeType::PROCEDURE);
	REQUIRE(procedure->getValue() == "conditionalExpressions");

	std::vector<std::shared_ptr<ASTNode>> statements = procedure->getChildByIndex(0)->getChildren();

	REQUIRE(statements.size() == 20);

	for (int i = 0; i < statements.size(); i++) {
		std::shared_ptr<ASTNode> statement = statements[i];
		REQUIRE(statement->getType() == ASTNodeType::WHILE);

		std::shared_ptr<ASTNode> contents = statement->getChildByIndex(1)->getChildByIndex(0);
		REQUIRE(contents->getType() == ASTNodeType::READ);
		REQUIRE(contents->getChildByIndex(0)->getValue() == "x");
	}
	std::filesystem::remove(filename);
}

TEST_CASE("Multiple procedures, all names that may be potential keywords.") {
	// Generate test file
	std::string filename = "sample.txt";
	std::string sampleProgram =
		"procedure assign { read x; }"
		"procedure call { read x; }"
		"procedure ant { read x; }"
		"procedure while { read x; }"
		"procedure if { read x; }"
		"procedure else { read x; }"
		"procedure then { read x; }"
		"procedure print { read x; }"
		"procedure read { read x; }"
		"procedure stmtLst { read x; }"
		"procedure variable { read x; }"
		"procedure stmt { read x; }"
		"procedure procedure { read x; }"
		"procedure program { read x; }"
		"procedure Follows { read x; }"
		"procedure FollowsT { read x; }"
		"procedure Parent { read x; }"
		"procedure ParentT { read x; }"
		"procedure Uses { read x; }"
		"procedure UsesP { read x; }"
		"procedure UsesS { read x; }"
		"procedure Modifies { read x; }"
		"procedure ModifiesP { read x; }"
		"procedure ModifiesS { read x; }"
		"procedure Calls { read x; }"
		"procedure CallsT { read x; }"
		"procedure Next { read x; }"
		"procedure NextT { read x; }"
		"procedure Affects { read x; }"
		"procedure AffectsT { read x; }";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->getType() == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->getLineNumber() == -1);
	REQUIRE(tree_ptr->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::PROGRAMS)->second);

	REQUIRE(tree_ptr->getChildren().size() == 30);
	std::filesystem::remove(filename);
}

TEST_CASE("Parsing single program with all possible statements types.") {
	std::string filename = "sample.txt";
	std::string sampleProgram =
		"procedure procedure {"
		"	while (!(read > procedure)) {"
		"	if = if;"
		"	} "
		""
		"	if (then < 2) then {"
		"		else = else;"
		"	} else {"
		"		while = then;"
		"	}"
		""
		"	read = 1 + program;"
		""
		"	call call;"
		"	print read;"
		"	read print;"
		"} procedure call { print k; }";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	std::vector<std::shared_ptr<ASTNode>> statements = tree_ptr->getChildByIndex(0)->getChildByIndex(0)->getChildren();
	REQUIRE(statements.size() == 6);

	SECTION("Testing While Statement") {
		std::shared_ptr<ASTNode> whileStatement = statements[0];
		REQUIRE(whileStatement->getType() == ASTNodeType::WHILE);
		REQUIRE(whileStatement->getLineNumber() == 1);
		REQUIRE(whileStatement->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::WHILE)->second);

		std::vector<std::shared_ptr<ASTNode>> whileChildren = whileStatement->getChildren();
		REQUIRE(whileChildren.size() == 2);

		SECTION("Testing predicates tree child node") {
			REQUIRE(whileChildren[0]->getType() == ASTNodeType::NOT);

			std::shared_ptr<ASTNode> cond_expr = whileChildren[0]->getChildByIndex(0);

			REQUIRE(cond_expr->getType() == ASTNodeType::GREATER);
			REQUIRE(cond_expr->getLineNumber() == 1);
			REQUIRE(cond_expr->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::GREATER)->second);

			std::vector<std::shared_ptr<ASTNode>> children = cond_expr->getChildren();
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->getLineNumber() == 1);
			REQUIRE(children[0]->getValue() == "read");

			REQUIRE(children[1]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[1]->getLineNumber() == 1);
			REQUIRE(children[1]->getValue() == "procedure");
		}

		SECTION("Testing Statement List tree child node") {
			REQUIRE(whileChildren[1]->getType() == ASTNodeType::STATEMENT_LIST);
			std::shared_ptr<ASTNode> statement = whileChildren[1]->getChildByIndex(0);

			REQUIRE(statement->getType() == ASTNodeType::ASSIGN);
			REQUIRE(statement->getLineNumber() == 2);
			REQUIRE(statement->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::ASSIGN)->second);

			std::vector<std::shared_ptr<ASTNode>> children = statement->getChildren();
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->getLineNumber() == 2);
			REQUIRE(children[0]->getValue() == "if");

			REQUIRE(children[1]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[1]->getLineNumber() == 2);
			REQUIRE(children[1]->getValue() == "if");
		}
	}

	SECTION("Testing if-then-else statement") {
		std::shared_ptr<ASTNode> ifStatement = statements[1];

		REQUIRE(ifStatement->getType() == ASTNodeType::IF_ELSE_THEN);
		REQUIRE(ifStatement->getLineNumber() == 3);
		REQUIRE(ifStatement->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::IF_ELSE_THEN)->second);

		std::vector<std::shared_ptr<ASTNode>> ifChildren = ifStatement->getChildren();
		REQUIRE(ifChildren.size() == 3);

		SECTION("Testing predicates tree child node") {
			std::shared_ptr<ASTNode> cond_expr = ifChildren[0];

			REQUIRE(cond_expr->getType() == ASTNodeType::LESSER);
			REQUIRE(cond_expr->getLineNumber() == 3);
			REQUIRE(cond_expr->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::LESSER)->second);

			std::vector<std::shared_ptr<ASTNode>> children = cond_expr->getChildren();
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->getLineNumber() == 3);
			REQUIRE(children[0]->getValue() == "then");

			REQUIRE(children[1]->getType() == ASTNodeType::CONSTANT);
			REQUIRE(children[1]->getLineNumber() == 3);
			REQUIRE(children[1]->getValue() == "2");
		}

		SECTION("Testing If-then statement list node") {
			REQUIRE(ifChildren[1]->getType() == ASTNodeType::STATEMENT_LIST);
			std::shared_ptr<ASTNode> statement = ifChildren[1]->getChildByIndex(0);

			REQUIRE(statement->getType() == ASTNodeType::ASSIGN);
			REQUIRE(statement->getLineNumber() == 4);
			REQUIRE(statement->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::ASSIGN)->second);

			std::vector<std::shared_ptr<ASTNode>> children = statement->getChildren();
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->getLineNumber() == 4);
			REQUIRE(children[0]->getValue() == "else");

			REQUIRE(children[1]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[1]->getLineNumber() == 4);
			REQUIRE(children[1]->getValue() == "else");
		}

		SECTION("Testing Else statement list node") {
			REQUIRE(ifChildren[1]->getType() == ASTNodeType::STATEMENT_LIST);
			std::shared_ptr<ASTNode> statement = ifChildren[2]->getChildByIndex(0);

			REQUIRE(statement->getType() == ASTNodeType::ASSIGN);
			REQUIRE(statement->getLineNumber() == 5);
			REQUIRE(statement->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::ASSIGN)->second);

			std::vector<std::shared_ptr<ASTNode>> children = statement->getChildren();
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->getLineNumber() == 5);
			REQUIRE(children[0]->getValue() == "while");

			REQUIRE(children[1]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[1]->getLineNumber() == 5);
			REQUIRE(children[1]->getValue() == "then");
		}
	}

	SECTION("Testing assign statement") {
		std::shared_ptr<ASTNode> assignStatement = statements[2];

		REQUIRE(assignStatement->getType() == ASTNodeType::ASSIGN);
		REQUIRE(assignStatement->getLineNumber() == 6);
		REQUIRE(assignStatement->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::ASSIGN)->second);

		SECTION("Testing tree child node") {
			std::vector<std::shared_ptr<ASTNode>> children = assignStatement->getChildren();
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->getLineNumber() == 6);
			REQUIRE(children[0]->getValue() == "read");

			REQUIRE(children[1]->getType() == ASTNodeType::ADD);
			REQUIRE(children[1]->getLineNumber() == 6);
			REQUIRE(children[1]->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::ADD)->second);

			SECTION("Testing expression of children") {
				std::vector<std::shared_ptr<ASTNode>> constants = children[1]->getChildren();
				REQUIRE(constants.size() == 2);
				REQUIRE(constants[0]->getType() == ASTNodeType::CONSTANT);
				REQUIRE(constants[0]->getLineNumber() == 6);
				REQUIRE(constants[0]->getValue() == "1");

				REQUIRE(constants[1]->getType() == ASTNodeType::VARIABLE);
				REQUIRE(constants[1]->getLineNumber() == 6);
				REQUIRE(constants[1]->getValue() == "program");
			}
		}
	}

	SECTION("Testing call statement") {
		std::shared_ptr<ASTNode> callStatement = statements[3];
		REQUIRE(callStatement->getType() == ASTNodeType::CALL);
		REQUIRE(callStatement->getLineNumber() == 7);
		REQUIRE(callStatement->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::CALL)->second);

		SECTION("Testing tree child node") {
			std::vector<std::shared_ptr<ASTNode>> children = callStatement->getChildren();
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->getType() == ASTNodeType::PROCEDURE);
		}
	}

	SECTION("Testing print statement") {
		std::shared_ptr<ASTNode> printStatement = statements[4];
		REQUIRE(printStatement->getType() == ASTNodeType::PRINT);
		REQUIRE(printStatement->getLineNumber() == 8);
		REQUIRE(printStatement->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::PRINT)->second);

		SECTION("Testing tree child node") {
			std::vector<std::shared_ptr<ASTNode>> children = printStatement->getChildren();
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->getLineNumber() == 8);
			REQUIRE(children[0]->getValue() == "read");
		}
	}

	SECTION("Testing read statement") {
		std::shared_ptr<ASTNode> readStatement = statements[5];
		REQUIRE(readStatement->getType() == ASTNodeType::READ);
		REQUIRE(readStatement->getLineNumber() == 9);
		REQUIRE(readStatement->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::READ)->second);

		SECTION("Testing tree child node") {
			std::vector<std::shared_ptr<ASTNode>> children = readStatement->getChildren();
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->getType() == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->getLineNumber() == 9);
			REQUIRE(children[0]->getValue() == "print");
		}
	}
	std::filesystem::remove(filename);
}

TEST_CASE("Calling parseProgram for complex procedure", "[parse][program]") {
	std::string filename = "sample.txt";
	std::string sampleProgram =
		"procedure computeCentroid {"
		"	count = 0;"
		"	cenX = 0;"
		"	cenY = 0;"
		"	while ((x != 0) && (y != 0)) {"
		"		count = count + 1;"
		"		cenX = cenX + x;"
		"		cenY = cenY + y;"
		"		call readPoint;"
		"	}"
		"	if (count == 0) then {"
		"		flag = 1;"
		"	} else {"
		"		cenX = cenX / count ;"
		"		cenY = cenY / count ;"
		"	}"
		"	normSq = cenX * cenX + cenY * cenY;"
		"}"
		""
		"procedure procedure {"
		"	print k;"
		"}"
		""
		"procedure readPoint {"
		"	read x;"
		"	read y;"
		"}";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->getType() == ASTNodeType::PROGRAMS);
	std::shared_ptr<ASTNode> procedure = tree_ptr->getChildByIndex(0);

	// Checking procedure node
	REQUIRE(procedure->getType() == ASTNodeType::PROCEDURE);
	REQUIRE(procedure->getValue() == "computeCentroid");

	std::vector<std::shared_ptr<ASTNode>> statements = procedure->getChildByIndex(0)->getChildren();

	// Check the statements of the parsed code
	REQUIRE(statements.size() == 6);

	std::shared_ptr<ASTNode> firstStmt = statements[0];

	// Check the first statement
	REQUIRE(firstStmt->getType() == ASTNodeType::ASSIGN);
	std::vector<std::shared_ptr<ASTNode>> firstStmtChildren = firstStmt->getChildren();

	REQUIRE(firstStmtChildren.size() == 2);
	REQUIRE(firstStmtChildren[0]->getType() == ASTNodeType::VARIABLE);
	REQUIRE(firstStmtChildren[0]->getValue() == "count");
	REQUIRE(firstStmtChildren[1]->getType() == ASTNodeType::CONSTANT);
	REQUIRE(firstStmtChildren[1]->getValue() == "0");

	std::shared_ptr<ASTNode> lastStmt = statements[5];

	// Check the last statement
	REQUIRE(lastStmt->getType() == ASTNodeType::ASSIGN);
	std::vector<std::shared_ptr<ASTNode>> lastStmtChildren = lastStmt->getChildren();
	REQUIRE(lastStmtChildren.size() == 2);
	REQUIRE(lastStmtChildren[0]->getType() == ASTNodeType::VARIABLE);
	REQUIRE(lastStmtChildren[0]->getValue() == "normSq");
	REQUIRE(lastStmtChildren[1]->getType() == ASTNodeType::ADD);

	std::vector<std::shared_ptr<ASTNode>> additionValues = lastStmtChildren[1]->getChildren();
	REQUIRE(additionValues.size() == 2);
	REQUIRE(additionValues[0]->getType() == ASTNodeType::MULTIPLY);
	REQUIRE(additionValues[1]->getType() == ASTNodeType::MULTIPLY);

	std::vector<std::shared_ptr<ASTNode>> firstExpr = additionValues[0]->getChildren();
	REQUIRE(firstExpr.size() == 2);
	REQUIRE(firstExpr[0]->getType() == ASTNodeType::VARIABLE);
	REQUIRE(firstExpr[0]->getValue() == "cenX");
	REQUIRE(firstExpr[1]->getType() == ASTNodeType::VARIABLE);
	REQUIRE(firstExpr[1]->getValue() == "cenX");

	std::vector<std::shared_ptr<ASTNode>> lastExpr = additionValues[1]->getChildren();
	REQUIRE(lastExpr.size() == 2);
	REQUIRE(lastExpr[0]->getType() == ASTNodeType::VARIABLE);
	REQUIRE(lastExpr[0]->getValue() == "cenY");
	REQUIRE(lastExpr[1]->getType() == ASTNodeType::VARIABLE);
	REQUIRE(lastExpr[1]->getValue() == "cenY");
	std::filesystem::remove(filename);
}

TEST_CASE("Parsing single procedure that contains 20 nested while loops.") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure nestedWhile {"
		"while (x == 2) {"
		"while (x != 2) {"
		"while (x < 2) {"
		"while (x <= 2) {"
		"while (x > 2) {"
		"while (x >= 2) {"
		"while (!(x == 2)) {"
		"while (0 == 2147483647) {"
		"while (0 != 2147483647) {"
		"while (0 < 2147483647) {"
		"while (0 <= 2147483647) {"
		"while (0 > 2147483647) {"
		"while (0 >= 2147483647) {"
		"while (!(0 == 2147483647)) {"
		"while ((x == 2) && (x == 1)) {"
		"while ((x != 2) || (x != 2)) {"
		"while ((!(x == 2)) && (!(x == 1))) {"
		"while (((x == 2) && (x == 1)) || (x == 3)) {"
		"while (!(!(!(!(!(!(!(!(!(!(x == 3))))))))))) {"
		"while (((x <= y) || (!(y == z))) && (!(z >= x))) {"
		"read x; }}}}}}}}}}}}}}}}}}}}}";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	std::shared_ptr<ASTNode> loop = tree_ptr->getChildByIndex(0)->getChildByIndex(0)->getChildByIndex(0);
	int line = 1;

	while (line <= 20) {
		REQUIRE(loop->getType() == ASTNodeType::WHILE);
		REQUIRE(loop->getLineNumber() == line);
		loop = loop->getChildByIndex(1)->getChildByIndex(0);
		line++;
	}

	REQUIRE(loop->getType() == ASTNodeType::READ);
	REQUIRE(loop->getLineNumber() == line);
	std::filesystem::remove(filename);
}

TEST_CASE("Parsing single procedure with nested while and if.") {
	std::string filename = "sample.txt";
	std::string sampleProgram =
		"procedure nestedIfWhile {"
		"	while (x == y) {"
		"		if (x == y) then {"
		"			while(x > y) {"
		"				read x;"
		"			}"
		""
		"			while (y > x) {"
		"				read y;"
		"			}"
		"		} else {"
		"			if (x != y) then {"
		"				while(!(x == y)) {"
		"					read y;"
		"				}"
		"			} else {"
		"				while (x >= y) {"
		"					read y;"
		"				}"
		"			}"
		""
		"			if (x >= y) then {"
		"				while(x <= y) {"
		"					read y;"
		"				}"
		"			} else {"
		"				while ((y > x) || (!(y == x))) {"
		"					read y;"
		"				}"
		"			}"
		"		}"
		"	}"
		"}";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();
	std::shared_ptr<ASTNode> loop = tree_ptr->getChildByIndex(0)->getChildByIndex(0)->getChildByIndex(0);
	REQUIRE(loop->getType() == ASTNodeType::WHILE);
	REQUIRE(loop->getLineNumber() == 1);
	loop = loop->getChildByIndex(1)->getChildByIndex(0);

	REQUIRE(loop->getType() == ASTNodeType::IF_ELSE_THEN);
	REQUIRE(loop->getLineNumber() == 2);

	SECTION("Testing internal If-then.") {
		std::vector<std::shared_ptr<ASTNode>> ifThenStatementList = loop->getChildByIndex(1)->getChildren();
		REQUIRE(ifThenStatementList.size() == 2);

		REQUIRE(ifThenStatementList[0]->getType() == ASTNodeType::WHILE);
		REQUIRE(ifThenStatementList[0]->getLineNumber() == 3);

		REQUIRE(ifThenStatementList[1]->getType() == ASTNodeType::WHILE);
		REQUIRE(ifThenStatementList[1]->getLineNumber() == 5);
	}

	SECTION("Testing internal Else.") {
		std::vector<std::shared_ptr<ASTNode>> elseStatementList = loop->getChildByIndex(2)->getChildren();
		REQUIRE(elseStatementList.size() == 2);

		SECTION("Testing first if-else.") {
			std::shared_ptr<ASTNode> if1 = elseStatementList[0];
			REQUIRE(if1->getType() == ASTNodeType::IF_ELSE_THEN);
			REQUIRE(if1->getLineNumber() == 7);

			std::shared_ptr<ASTNode> if1while1 = if1->getChildByIndex(1)->getChildByIndex(0);
			REQUIRE(if1while1->getType() == ASTNodeType::WHILE);
			REQUIRE(if1while1->getLineNumber() == 8);

			std::shared_ptr<ASTNode> if1while2 = if1->getChildByIndex(2)->getChildByIndex(0);
			REQUIRE(if1while2->getType() == ASTNodeType::WHILE);
			REQUIRE(if1while2->getLineNumber() == 10);
		}

		SECTION("Testing second if-else.") {
			std::shared_ptr<ASTNode> if2 = elseStatementList[1];
			REQUIRE(if2->getType() == ASTNodeType::IF_ELSE_THEN);
			REQUIRE(if2->getLineNumber() == 12);

			std::shared_ptr<ASTNode> if2while1 = if2->getChildByIndex(1)->getChildByIndex(0);
			REQUIRE(if2while1->getType() == ASTNodeType::WHILE);
			REQUIRE(if2while1->getLineNumber() == 13);

			std::shared_ptr<ASTNode> if2while2 = if2->getChildByIndex(2)->getChildByIndex(0);
			REQUIRE(if2while2->getType() == ASTNodeType::WHILE);
			REQUIRE(if2while2->getLineNumber() == 15);
		}
	}
	std::filesystem::remove(filename);
}

TEST_CASE("Parse program with whitespace in the token stream.") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure main { read helloWorld; } \n\n";
	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->getType() == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::PROGRAMS)->second);

	std::vector<std::shared_ptr<ASTNode>> procedures = tree_ptr->getChildren();
	REQUIRE(procedures.size() == 1);

	REQUIRE(procedures[0]->getType() == ASTNodeType::PROCEDURE);
	REQUIRE(procedures[0]->getValue() == "main");

	std::shared_ptr<ASTNode> statement = procedures[0]->getChildByIndex(0)->getChildByIndex(0);
	REQUIRE(statement->getType() == ASTNodeType::READ);
	REQUIRE(statement->getLineNumber() == 1);
	REQUIRE(statement->getChildByIndex(0)->getValue() == "helloWorld");

	std::filesystem::remove(filename);
}

TEST_CASE("Simple program with a lot of white spaces") {
	std::string filename = "sample.txt";
	std::string sampleProgram = 
		"\n\n\n\n\n\n procedure \n\n\n\n\n\n main \n\n\n\n\n\n { \n\n\n\n\n\n"
		"\n\n\n\n\n\n\n\n read \n\n\n\n\n\n\n\n\n\n helloWorld \n\n\n\n\n\n ;"
		"\n\n\n\n } \n\n\n\n\n\n\n\n\n\n\n\n";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->getType() == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::PROGRAMS)->second);

	std::vector<std::shared_ptr<ASTNode>> procedures = tree_ptr->getChildren();
	REQUIRE(procedures.size() == 1);

	REQUIRE(procedures[0]->getType() == ASTNodeType::PROCEDURE);
	REQUIRE(procedures[0]->getValue() == "main");

	std::shared_ptr<ASTNode> statement = procedures[0]->getChildByIndex(0)->getChildByIndex(0);
	REQUIRE(statement->getType() == ASTNodeType::READ);
	REQUIRE(statement->getLineNumber() == 1);
	REQUIRE(statement->getChildByIndex(0)->getValue() == "helloWorld");
	std::filesystem::remove(filename);
}

TEST_CASE("Long assignment statement") {
	std::string filename = "sample.txt";
	std::string sampleProgram =
		    "procedure LongAssign {"
		    "x = 1 / 2  / 3  * 4  * 5  % 6  * 7  * 8  * 9  - 10"
		    "    + 11  * 12  % 13  % 14  / 15  / 16  % 17  % 18  % 19  / 20"
			"    + 21  + 22  % 23  / 24  - 25  / 26  + 27  % 28  % 29  % 30"
			"    / 31  - 32  / 33  * 34  * 35  * 36  - 37  - 38  - 39  + 40"
			"    * 41  * 42  - 43  * 44  - 45  + 46  + 47  * 48  + 49  - 50"
			"    - 51  * 52  + 53  - 54  * 55  / 56  + 57  - 58  / 59  + 60"
			"    % 61  + 62  / 63  * 64  + 65  % 66  % 67  + 68  % 69  + 70"
			"    / 71  + 72  + 73  + 74  - 75  + 76  % 77  / 78  - 79  * 80"
			"    - 81  * 82  * 83  * 84  - 85  + 86  + 87  * 88  / 89  % 90"
			"    - 91  - 92  - 93  - 94  - 95  - 96  * 97  * 98  / 99  + 100"
			"    - 101  / 102  - 103  / 104  - 105  + 106  % 107  % 108  / 109  + 110"
			"    * 111  % 112  - 113  % 114  * 115  / 116  % 117  - 118  + 119  * 120"
			"    % 121  % 122  + 123  % 124  % 125  + 126  % 127  % 128  + 129  + 130"
			"    % 131  / 132  / 133  * 134  * 135  / 136  % 137  % 138  + 139  - 140"
			"    - 141  % 142  * 143  * 144  + 145  / 146  % 147  * 148  - 149  * 150"
			"    - 151  / 152  / 153  % 154  + 155  / 156  % 157  - 158  + 159  / 160"
			"    - 161  * 162  * 163  / 164  / 165  - 166  + 167  - 168  + 169  / 170"
			"    + 171  * 172  - 173  - 174  * 175  - 176  * 177  % 178  - 179  * 180"
			"    % 181  / 182  - 183  + 184  % 185  + 186  % 187  % 188  + 189  * 190"
			"    % 191  % 192  / 193  * 194  / 195  * 196  + 197  % 198  + 199  % 200"
			"    - 201  - 202  - 203  % 204  - 205  + 206  - 207  % 208  + 209  * 210"
			"    + 211  / 212  * 213  + 214  - 215  + 216  - 217  + 218  - 219  + 220"
			"    - 221  / 222  * 223  / 224  - 225  % 226  % 227  * 228  - 229  / 230"
			"    * 231  + 232  / 233  % 234  % 235  - 236  / 237  + 238  / 239  * 240"
			"    % 241  - 242  / 243  * 244  * 245  + 246  - 247  - 248  - 249  / 250"
			"    + 251  + 252  * 253  % 254  % 255  + 256  * 257  - 258  * 259  - 260"
			"    % 261  + 262  - 263  * 264  + 265  / 266  / 267  * 268  + 269  / 270"
			"    + 271  + 272  + 273  * 274  + 275  - 276  * 277  - 278  / 279  * 280"
			"    + 281  * 282  * 283  - 284  / 285  + 286  * 287  % 288  / 289  + 290"
			"    * 291  * 292  % 293  / 294  / 295  % 296  - 297  % 298  % 299  / 300"
			"    / 301  - 302  % 303  % 304  - 305  * 306  - 307  % 308  / 309  % 310"
			"    % 311  + 312  % 313  * 314  % 315  * 316  % 317  + 318  % 319  % 320"
			"    + 321  * 322  + 323  - 324  * 325  + 326  % 327  / 328  / 329  / 330"
			"    + 331  % 332  - 333  * 334  % 335  - 336  / 337  * 338  - 339  + 340"
			"    - 341  * 342  * 343  + 344  % 345  - 346  + 347  - 348  / 349  / 350"
			"    - 351  / 352  * 353  % 354  * 355  % 356  / 357  / 358  + 359  + 360"
			"    - 361  + 362  - 363  - 364  * 365  * 366  / 367  - 368  * 369  * 370"
			"    - 371  % 372  - 373  / 374  / 375  + 376  + 377  + 378  * 379  * 380"
			"    / 381  % 382  * 383  % 384  + 385  * 386  / 387  / 388  + 389  + 390"
			"    * 391  + 392  / 393  - 394  * 395  / 396  % 397  % 398  * 399  % 400"
			"    + 401  + 402  / 403  % 404  / 405  + 406  % 407  % 408  / 409  * 410"
			"    / 411  + 412  + 413  - 414  * 415  * 416  * 417  * 418  / 419  + 420"
			"    - 421  + 422  / 423  - 424  / 425  * 426  * 427  % 428  - 429  + 430"
			"    - 431  % 432  - 433  % 434  + 435  * 436  - 437  * 438  - 439  - 440"
			"    - 441  - 442  * 443  + 444  * 445  + 446  / 447  * 448  % 449  - 450"
			"    + 451  - 452  * 453  / 454  / 455  + 456  * 457  % 458  / 459  / 460"
			"    + 461  * 462  * 463  - 464  - 465  / 466  % 467  / 468  * 469  * 470"
			"    - 471  % 472  + 473  / 474  % 475  - 476  / 477  - 478  / 479  - 480"
			"    / 481  - 482  % 483  % 484  / 485  + 486  / 487  + 488  * 489  / 490"
			"    % 491  / 492  / 493  + 494  - 495  / 496  % 497  + 498  - 499  * 500"
			"    % 501  + 502  % 503  % 504  * 505  % 506  / 507  + 508  - 509  / 510"
			"    + 511  + 512  - 513  * 514  % 515  % 516  + 517  / 518  % 519  / 520"
			"    + 521  + 522  - 523  * 524  - 525  * 526  - 527  * 528  - 529  / 530"
			"    * 531  / 532  + 533  % 534  + 535  % 536  / 537  / 538  - 539  % 540"
			"    * 541  / 542  - 543  * 544  % 545  * 546  * 547  * 548  % 549  % 550"
			"    % 551  - 552  / 553  + 554  + 555  - 556  + 557  / 558  % 559  % 560"
			"    % 561  * 562  % 563  + 564  - 565  + 566  / 567  % 568  / 569  * 570"
			"    - 571  * 572  * 573  + 574  % 575  % 576  - 577  / 578  + 579  % 580"
			"    % 581  / 582  - 583  - 584  * 585  % 586  * 587  - 588  / 589  / 590"
			"    * 591  + 592  + 593  - 594  % 595  * 596  + 597  - 598  + 599  * 600"
			"    / 601  - 602  % 603  - 604  + 605  / 606  + 607  + 608  % 609  + 610"
			"    - 611  * 612  / 613  - 614  % 615  % 616  - 617  / 618  * 619  + 620"
			"    % 621  % 622  / 623  - 624  % 625  / 626  / 627  % 628  + 629  + 630"
			"    % 631  * 632  + 633  % 634  - 635  * 636  / 637  % 638  * 639  + 640"
			"    + 641  + 642  / 643  + 644  % 645  * 646  % 647  % 648  + 649  * 650"
			"    % 651  / 652  * 653  / 654  * 655  * 656  % 657  % 658  / 659  % 660"
			"    - 661  + 662  - 663  / 664  * 665  * 666  / 667  + 668  + 669  * 670"
			"    + 671  % 672  / 673  / 674  * 675  - 676  * 677  + 678  * 679  % 680"
			"    + 681  + 682  * 683  / 684  / 685  % 686  * 687  % 688  / 689  - 690"
			"    * 691  + 692  % 693  - 694  * 695  % 696  + 697  % 698  + 699  - 700"
			"    - 701  + 702  * 703  + 704  - 705  + 706  * 707  % 708  * 709  * 710"
			"    / 711  + 712  / 713  + 714  % 715  - 716  / 717  / 718  + 719  + 720"
			"    - 721  * 722  * 723  / 724  * 725  - 726  + 727  % 728  + 729  * 730"
			"    + 731  / 732  / 733  % 734  + 735  + 736  / 737  + 738  * 739  * 740"
			"    - 741  % 742  * 743  - 744  - 745  % 746  + 747  * 748  % 749  / 750"
			"    % 751  - 752  + 753  - 754  + 755  + 756  * 757  + 758  / 759  * 760"
			"    % 761  % 762  * 763  / 764  - 765  * 766  / 767  - 768  + 769  % 770"
			"    / 771  / 772  * 773  % 774  * 775  * 776  - 777  - 778  * 779  % 780"
			"    - 781  % 782  % 783  - 784  / 785  % 786  - 787  + 788  * 789  + 790"
			"    - 791  - 792  * 793  - 794  - 795  * 796  - 797  % 798  - 799  - 800"
			"    % 801  % 802  - 803  / 804  - 805  + 806  / 807  + 808  % 809  / 810"
			"    + 811  + 812  - 813  * 814  - 815  * 816  + 817  / 818  % 819  + 820"
			"    % 821  + 822  * 823  % 824  % 825  / 826  - 827  + 828  + 829  + 830"
			"    * 831  / 832  / 833  * 834  % 835  / 836  - 837  + 838  * 839  * 840"
			"    % 841  - 842  / 843  - 844  / 845  / 846  / 847  / 848  * 849  - 850"
			"    / 851  - 852  * 853  + 854  + 855  + 856  / 857  / 858  % 859  - 860"
			"    * 861  - 862  / 863  % 864  - 865  % 866  + 867  - 868  - 869  * 870"
			"    - 871  * 872  / 873  * 874  / 875  - 876  + 877  * 878  / 879  + 880"
			"    - 881  % 882  / 883  / 884  % 885  - 886  / 887  % 888  * 889  - 890"
			"    + 891  * 892  * 893  * 894  + 895  / 896  * 897  % 898  / 899  * 900"
			"    / 901  * 902  - 903  / 904  % 905  - 906  + 907  - 908  - 909  * 910"
			"    / 911  - 912  % 913  % 914  / 915  % 916  - 917  + 918  + 919  % 920"
			"    / 921  + 922  - 923  + 924  + 925  - 926  - 927  % 928  / 929  - 930"
			"    + 931  % 932  * 933  - 934  + 935  % 936  % 937  + 938  % 939  + 940"
			"    / 941  + 942  % 943  - 944  % 945  + 946  - 947  / 948  % 949  % 950"
			"    - 951  % 952  * 953  / 954  - 955  * 956  + 957  * 958  % 959  * 960"
			"    - 961  % 962  - 963  / 964  / 965  * 966  / 967  % 968  % 969  % 970"
			"    * 971  / 972  - 973  - 974  - 975  - 976  % 977  % 978  * 979  * 980"
			"    % 981  * 982  - 983  / 984  / 985  * 986  % 987  / 988  % 989  / 990"
			"    * 991  - 992  / 993  + 994  % 995  + 996  * 997  % 998  % 999  / 1000;"
			"}";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->getType() == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->getValue() == ASTUtility::getASTNodeType.find(ASTNodeType::PROGRAMS)->second);

	std::vector<std::shared_ptr<ASTNode>> procedures = tree_ptr->getChildren();
	REQUIRE(procedures.size() == 1);

	REQUIRE(procedures[0]->getType() == ASTNodeType::PROCEDURE);
	REQUIRE(procedures[0]->getValue() == "LongAssign");

	std::shared_ptr<ASTNode> statement = procedures[0]->getChildByIndex(0)->getChildByIndex(0);
	REQUIRE(statement->getType() == ASTNodeType::ASSIGN);
	REQUIRE(statement->getLineNumber() == 1);
	REQUIRE(statement->getChildByIndex(0)->getValue() == "x");

	// Scan the AST tree and count each of the numbers 1-1000
		// Number of constants in the program
	const int numConsts = 1000;
	bool foundAll = true;

	// Container to store if a constant is found
	std::vector<bool> found(numConsts + 1, false);

	// Function to recursively search for constants in the AST
	std::function<void(std::shared_ptr<ASTNode>)> findConst = [&](std::shared_ptr<ASTNode> node) {
		if (node->getType() == ASTNodeType::CONSTANT) {
			int value = std::stoi(node->getValue());
			found[value] = true;
		}

		// Searching in each child of the current node
		for (auto& child : node->getChildren()) {
			findConst(child);
		}
		};

	// Searching for constants in the AST
	findConst(statement);

	// Ensuring if all constants from 1 to 'numConsts' are found
	for (int i = 1; i <= numConsts; ++i) {
		if (!found[i]) {
			foundAll = false;
		}
	}

	REQUIRE(foundAll);
	std::filesystem::remove(filename);
}
