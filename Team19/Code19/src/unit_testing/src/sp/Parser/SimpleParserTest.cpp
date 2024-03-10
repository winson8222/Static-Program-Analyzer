#include "catch.hpp"
#include "sp/Parser/SimpleParserFacade.h"
#include <iostream>
#include <filesystem>
#include <fstream>

TEST_CASE("Program parsing throws an error for missing curly brace after procedure end.") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure proc1 {\n"
                                "\tprint x;\n"
                                "\n"
                                "procedure proc2 \n"
                                "\tcall y;\n"
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
    std::string sampleProgram = "procedure invalidProcedure {\n"
                                "\tcall y;";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    SimpleParserFacade parser(filename);
    CHECK_THROWS_AS(parser.parse(), std::runtime_error);
    std::filesystem::remove(filename);}

TEST_CASE("Program parsing throws an error for missing curly braces.") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure invalidProcedure \n"
                                "\tcall y;";
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
    std::string sampleProgram = "procedure proc {\n"
                                "\tcall variable123;\n"
                                "\tprint xyz call;\n"
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

TEST_CASE("Program parsing throws an error for missing parenthesis around !(cond_expr) with following && operator.") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure procedure {\n"
                                "\twhile (!(read != 11) && !(read == while)) {\n"
                                "\t\tprint = 0;\n"
                                "\t}\n"
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
    std::string sampleProgram = "procedure procedure {\n"
                                "\twhile ((read != 11)) {\n"
                                "\t\tprint = 0;\n"
                                "\t}\n"
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
    std::string sampleProgram = "procedure main {\n"
                                "\twrite x;\n"
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

TEST_CASE("Single procedure, with read statement") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure main {\n"
                                "\tread helloWorld;\n"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->value == ASTUtility::getASTNodeType.find(ASTNodeType::PROGRAMS)->second);


	const auto& procedures = tree_ptr->children;
	REQUIRE(procedures.size() == 1);

	REQUIRE(procedures[0]->type == ASTNodeType::PROCEDURE);
	REQUIRE(procedures[0]->value == "main");

	const auto& statement = ((procedures[0]->children)[0]->children)[0];
	REQUIRE(statement->type == ASTNodeType::READ);
	REQUIRE(statement->lineNumber == 1);
	REQUIRE(statement->children[0]->value == "helloWorld");
    std::filesystem::remove(filename);
}

TEST_CASE("Single procedure, all possible conditional expressions in while statements") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure conditionalExpressions {\n"
                                "\twhile(x == 2) {read x;}\n"
                                "\twhile(x != 2) {read x;}\n"
                                "\twhile(x < 2) {read x;}\n"
                                "\twhile(x <= 2) {read x;}\n"
                                "\twhile(x > 2) {read x;}\n"
                                "\twhile(x >= 2) {read x;}\n"
                                "\twhile(!(x == 2)) {read x;}\n"
                                "\n"
                                "\twhile(0 == 2147483647) {read x;}\n"
                                "\twhile(0 != 2147483647) {read x;}\n"
                                "\twhile(0 < 2147483647) {read x;}\n"
                                "\twhile(0 <= 2147483647) {read x;}\n"
                                "\twhile(0 > 2147483647) {read x;}\n"
                                "\twhile(0 >= 2147483647) {read x;}\n"
                                "\twhile(!(0 == 2147483647)) {read x;}\n"
                                "\n"
                                "\twhile((x == 2) && (x == 1)) {read x;}\n"
                                "\twhile((x != 2) || (x != 2)) {read x;}\n"
                                "\twhile((!(x == 2)) && (!(x == 1))) {read x;}\n"
                                "\twhile( ((x == 2) && (x == 1)) || (x == 3)) {read x;}\n"
                                "\twhile(!(!(!(!(!(!(!(!(!(!(x==3))))))))))) {read x;}\n"
                                "\twhile(((x <= y) || (!(y == z))) && (!(z >= x))) {read x;}\n"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();
	auto& procedure = (tree_ptr->children)[0];

	// Checking procedure node
	REQUIRE(procedure->type == ASTNodeType::PROCEDURE);
	REQUIRE(procedure->value == "conditionalExpressions");

	const auto& statements = (procedure->children)[0]->children;

	REQUIRE(statements.size() == 20);

	for (int i = 0; i < statements.size(); i++) {
		auto& statement = statements[i];
		REQUIRE(statement->type == ASTNodeType::WHILE);

		auto& contents = ((statement->children)[1]->children)[0];
		REQUIRE(contents->type == ASTNodeType::READ);
		REQUIRE((contents->children)[0]->value == "x");
	}
    std::filesystem::remove(filename);
}

TEST_CASE("Multiple procedures, all names that may be potential keywords.") {
	// Generate test file
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure assign { read x; }\n"
                                "procedure call { read x; }\n"
                                "procedure constant { read x; }\n"
                                "procedure while { read x; }\n"
                                "procedure if { read x; }\n"
                                "procedure else { read x; }\n"
                                "procedure then { read x; }\n"
                                "procedure print { read x; }\n"
                                "procedure read { read x; }\n"
                                "procedure stmtLst { read x; }\n"
                                "procedure variable { read x; }\n"
                                "procedure stmt { read x; }\n"
                                "procedure procedure { read x; }\n"
                                "procedure program { read x; }\n"
                                "procedure Follows { read x; }\n"
                                "procedure FollowsT { read x; }\n"
                                "procedure Parent { read x; }\n"
                                "procedure ParentT { read x; }\n"
                                "procedure Uses { read x; }\n"
                                "procedure UsesP { read x; }\n"
                                "procedure UsesS { read x; }\n"
                                "procedure Modifies { read x; }\n"
                                "procedure ModifiesP { read x; }\n"
                                "procedure ModifiesS { read x; }\n"
                                "procedure Calls { read x; }\n"
                                "procedure CallsT { read x; }\n"
                                "procedure Next { read x; }\n"
                                "procedure NextT { read x; }\n"
                                "procedure Affects { read x; }\n"
                                "procedure AffectsT { read x; }";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	REQUIRE(tree_ptr->type == ASTNodeType::PROGRAMS);
	REQUIRE(tree_ptr->lineNumber == -1);
	REQUIRE(tree_ptr->value == ASTUtility::getASTNodeType.find(ASTNodeType::PROGRAMS)->second);

	REQUIRE(tree_ptr->children.size() == 30);
    std::filesystem::remove(filename);
}

TEST_CASE("Parsing single program with all possible statements types.") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure procedure {\n"
                                "\twhile (!(read > procedure)) {\n"
                                "\t\tif = if;\n"
                                "\t} \n"
                                "\n"
                                "\tif (then < 2) then {\n"
                                "\t\telse = else;\n"
                                "\t} else {\n"
                                "\t\twhile = then;\n"
                                "\t}\n"
                                "\n"
                                "\tread = 1 + program;\n"
                                "\n"
                                "\tcall call;\n"
                                "\tprint read;\n"
                                "\tread print;\n"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	auto& statements = (((tree_ptr->children)[0]->children)[0]->children);
	REQUIRE(statements.size() == 6);

	SECTION("Testing While Statement") {
		std::shared_ptr<ASTNode> whileStatement = statements[0];
		REQUIRE(whileStatement->type == ASTNodeType::WHILE);
		REQUIRE(whileStatement->lineNumber == 1);
		REQUIRE(whileStatement->value == ASTUtility::getASTNodeType.find(ASTNodeType::WHILE)->second);

		auto& whileChildren = whileStatement->children;
		REQUIRE(whileChildren.size() == 2);

		SECTION("Testing predicates tree child node") {
			REQUIRE(whileChildren[0]->type == ASTNodeType::NOT);

			auto& cond_expr = (whileChildren[0]->children)[0];

			REQUIRE(cond_expr->type == ASTNodeType::GREATER);
			REQUIRE(cond_expr->lineNumber == 1);
			REQUIRE(cond_expr->value == ASTUtility::getASTNodeType.find(ASTNodeType::GREATER)->second);

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
			REQUIRE(statement->value == ASTUtility::getASTNodeType.find(ASTNodeType::ASSIGN)->second);

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
		REQUIRE(ifStatement->value == ASTUtility::getASTNodeType.find(ASTNodeType::IF_ELSE_THEN)->second);

		auto& ifChildren = ifStatement->children;
		REQUIRE(ifChildren.size() == 3);

		SECTION("Testing predicates tree child node") {
			auto& cond_expr = ifChildren[0];

			REQUIRE(cond_expr->type == ASTNodeType::LESSER);
			REQUIRE(cond_expr->lineNumber == 3);
			REQUIRE(cond_expr->value == ASTUtility::getASTNodeType.find(ASTNodeType::LESSER)->second);

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
			REQUIRE(statement->value == ASTUtility::getASTNodeType.find(ASTNodeType::ASSIGN)->second);

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
			REQUIRE(statement->value == ASTUtility::getASTNodeType.find(ASTNodeType::ASSIGN)->second);

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
		REQUIRE(assignStatement->value == ASTUtility::getASTNodeType.find(ASTNodeType::ASSIGN)->second);

		SECTION("Testing tree child node") {
			const auto& children = assignStatement->children;
			REQUIRE(children.size() == 2);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 6);
			REQUIRE(children[0]->value == "read");

			REQUIRE(children[1]->type == ASTNodeType::ADD);
			REQUIRE(children[1]->lineNumber == 6);
			REQUIRE(children[1]->value == ASTUtility::getASTNodeType.find(ASTNodeType::ADD)->second);

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
		REQUIRE(callStatement->value == ASTUtility::getASTNodeType.find(ASTNodeType::CALL)->second);

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
		REQUIRE(printStatement->value == ASTUtility::getASTNodeType.find(ASTNodeType::PRINT)->second);

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
		REQUIRE(readStatement->value == ASTUtility::getASTNodeType.find(ASTNodeType::READ)->second);

		SECTION("Testing tree child node") {
			const auto& children = readStatement->children;
			REQUIRE(children.size() == 1);
			REQUIRE(children[0]->type == ASTNodeType::VARIABLE);
			REQUIRE(children[0]->lineNumber == 9);
			REQUIRE(children[0]->value == "print");
		}
	}
    std::filesystem::remove(filename);
}

TEST_CASE("Calling parseProgram for complex procedure", "[parse][program]") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure computeCentroid {\n"
                                "\tcount = 0;\n"
                                "\tcenX = 0;\n"
                                "\tcenY = 0;\n"
                                "\twhile ((x != 0) && (y != 0)) {\n"
                                "\t\tcount = count + 1;\n"
                                "\t\tcenX = cenX + x;\n"
                                "\t\tcenY = cenY + y;\n"
                                "\t\tcall readPoint;\n"
                                "\t}\n"
                                "\tif (count == 0) then {\n"
                                "\t\tflag = 1;\n"
                                "\t} else {\n"
                                "\t\tcenX = cenX / count ;\n"
                                "\t\tcenY = cenY / count ;\n"
                                "\t}\n"
                                "\tnormSq = cenX * cenX + cenY * cenY;\n"
                                "}\n"
                                "\n"
                                "procedure procedure {\n"
                                "\tprint k;\n"
                                "}\n"
                                "\n"
                                "procedure readPoint {\n"
                                "\tread x;\n"
                                "\tread y;\n"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    SimpleParserFacade parser(filename);
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
    std::filesystem::remove(filename);
}

TEST_CASE("Parsing single procedure that contains 20 nested while loops.") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure nestedWhile {\n"
                                "\twhile (x == 2) {\n"
                                "\t\twhile (x != 2) {\n"
                                "\t\t\twhile (x < 2) {\n"
                                "\t\t\t\twhile (x <= 2) {\n"
                                "\t\t\t\t\twhile (x > 2) {\n"
                                "\t\t\t\t\t\twhile (x >= 2) {\n"
                                "\t\t\t\t\t\t\twhile (!(x == 2)) {\n"
                                "\t\t\t\t\t\t\t\twhile (0 == 2147483647) {\n"
                                "\t\t\t\t\t\t\t\t\twhile (0 != 2147483647) {\n"
                                "\t\t\t\t\t\t\t\t\t\twhile (0 < 2147483647) {\n"
                                "\t\t\t\t\t\t\t\t\t\t\twhile (0 <= 2147483647) {\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\twhile (0 > 2147483647) {\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\twhile (0 >= 2147483647) {\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\twhile (!(0 == 2147483647)) {\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\twhile ((x == 2) && (x == 1)) {\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\twhile ((x != 2) || (x != 2)) {\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\twhile ((!(x == 2)) && (!(x == 1))) {\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\twhile (((x == 2) && (x == 1)) || (x == 3)) {\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\twhile (!(!(!(!(!(!(!(!(!(!(x == 3))))))))))) {\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\twhile (((x <= y) || (!(y == z))) && (!(z >= x))) {\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\tread x;\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t\t}\n"
                                "\t\t\t\t\t}\n"
                                "\t\t\t\t}\n"
                                "\t\t\t}\n"
                                "\t\t}\n"
                                "\t}\n"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	auto& loop = ((tree_ptr->children)[0]->children)[0]->children[0];
	int line = 1;

	while (line <= 20) {
		REQUIRE(loop->type == ASTNodeType::WHILE);
		REQUIRE(loop->lineNumber == line);
		loop = (loop->children)[1]->children[0];
		line++;
	}

	REQUIRE(loop->type == ASTNodeType::READ);
	REQUIRE(loop->lineNumber == line);
    std::filesystem::remove(filename);
}

TEST_CASE("Parsing single procedure with nested while and if.") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure nestedIfWhile {\n"
                                "\twhile (x == y) {\n"
                                "\t\tif (x == y) then {\n"
                                "\t\t\twhile(x > y) {\n"
                                "\t\t\t\tread x;\n"
                                "\t\t\t}\n"
                                "\n"
                                "\t\t\twhile (y > x) {\n"
                                "\t\t\t\tread y;\n"
                                "\t\t\t}\n"
                                "\t\t} else {\n"
                                "\t\t\tif (x != y) then {\t\t\t\t\t\t\n"
                                "\t\t\t\twhile(!(x == y)) {\n"
                                "\t\t\t\t\tread y;\n"
                                "\t\t\t\t}\n"
                                "\t\t\t} else {\n"
                                "\t\t\t\twhile (x >= y) {\n"
                                "\t\t\t\t\tread y;\n"
                                "\t\t\t\t}\n"
                                "\t\t\t}\n"
                                "\n"
                                "\t\t\tif (x >= y) then {\n"
                                "\t\t\t\twhile(x <= y) {\n"
                                "\t\t\t\t\tread y;\n"
                                "\t\t\t\t}\n"
                                "\t\t\t} else {\n"
                                "\t\t\t\twhile ((y > x) || (!(y == x))) {\n"
                                "\t\t\t\t\tread y;\n"
                                "\t\t\t\t}\n"
                                "\t\t\t}\n"
                                "\t\t}\n"
                                "\t}\n"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	auto& loop = ((tree_ptr->children)[0]->children)[0]->children[0];
	REQUIRE(loop->type == ASTNodeType::WHILE);
	REQUIRE(loop->lineNumber == 1);
	loop = (loop->children)[1]->children[0];

	REQUIRE(loop->type == ASTNodeType::IF_ELSE_THEN);
	REQUIRE(loop->lineNumber == 2);

	SECTION("Testing internal If-then.") {
		auto& ifThenStatementList = (loop->children)[1]->children;
		REQUIRE(ifThenStatementList.size() == 2);

		REQUIRE(ifThenStatementList[0]->type == ASTNodeType::WHILE);
		REQUIRE(ifThenStatementList[0]->lineNumber == 3);

		REQUIRE(ifThenStatementList[1]->type == ASTNodeType::WHILE);
		REQUIRE(ifThenStatementList[1]->lineNumber == 5);
	}

	SECTION("Testing internal Else.") {
		auto& elseStatementList = (loop->children)[2]->children;
		REQUIRE(elseStatementList.size() == 2);

		SECTION("Testing first if-else.") {
			auto& if1 = elseStatementList[0];
			REQUIRE(if1->type == ASTNodeType::IF_ELSE_THEN);
			REQUIRE(if1->lineNumber == 7);
			
			auto& if1while1 = if1->children[1]->children[0];
			REQUIRE(if1while1->type == ASTNodeType::WHILE);
			REQUIRE(if1while1->lineNumber == 8);

			auto& if1while2 = if1->children[2]->children[0];
			REQUIRE(if1while2->type == ASTNodeType::WHILE);
			REQUIRE(if1while2->lineNumber == 10);
		}

		SECTION("Testing second if-else.") {
			auto& if2 = elseStatementList[1];
			REQUIRE(if2->type == ASTNodeType::IF_ELSE_THEN);
			REQUIRE(if2->lineNumber == 12);

			auto& if2while1 = if2->children[1]->children[0];
			REQUIRE(if2while1->type == ASTNodeType::WHILE);
			REQUIRE(if2while1->lineNumber == 13);

			auto& if2while2 = if2->children[2]->children[0];
			REQUIRE(if2while2->type == ASTNodeType::WHILE);
			REQUIRE(if2while2->lineNumber == 15);
		}
    }
    std::filesystem::remove(filename);
}
