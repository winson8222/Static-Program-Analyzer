#include "catch.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "sp/ControlFlow/SimpleControlFlow.h"
#include "sp/Parser/SimpleParserFacade.h"

TEST_CASE("Throw error for non-program type node") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure procedure { read = 1 + program; }";
	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> ast = parser.parse();
	REQUIRE_THROWS(SimpleControlFlow{ ast->getChildByIndex(0) });
}

TEST_CASE("CFG for single program with all possible statements types.") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure procedure {"
		"read = 1 + program;"               // 1
		"call call;"                        // 2
		"print read;"                       // 3
		"read print;"                       // 4
		"while (!(read > procedure)) {"     // 5
		"  if = if;"                        // 6
		"} "
		""
		"if (then < 2) then {"              // 7
		"  else = else;"                    // 8
		"} else {"
		"  while = then;"                   // 9
		"}"
		"}"
		""
		"procedure call { print k; }"       // 10
		;
	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> ast = parser.parse();
	SimpleControlFlow cfg(ast);
	std::vector<std::shared_ptr<CFGNode>> cfgGraphs = *(cfg.createControlFlowGraphs());

	SECTION("Check children number") {
		REQUIRE(cfgGraphs.size() == 2);

		auto& node = cfgGraphs[0];

		SECTION("Check procedures") {
			for (int i = 1; i <= 6; i++) {
				REQUIRE(node->getLineNumber() == i);
				node = (node->getChildren())[0];
			}

			REQUIRE(node->getLineNumber() == 5);

			node = (node->getChildren())[1];
			REQUIRE(node->getLineNumber() == 7);

			std::vector<std::shared_ptr<CFGNode>> ifElseStatement = node->getChildren();
			auto& ifBlockNode = ifElseStatement[0];
			auto& elseBlockNode = ifElseStatement[1];

			REQUIRE(ifBlockNode->getLineNumber() == 8);
			REQUIRE((ifBlockNode->getChildren()[0])->getLineNumber() == -1);

			REQUIRE(elseBlockNode->getLineNumber() == 9);
			REQUIRE((elseBlockNode->getChildren()[0])->getLineNumber() == -1);
		}

		node = cfgGraphs[1];
		SECTION("Check second procedure") {
			REQUIRE(node->getLineNumber() == 10);
			REQUIRE((node->getChildren()[0])->getLineNumber() == -1);
		}
	}
	std::filesystem::remove(filename);
}

TEST_CASE("CFG generation for multiple whiles in a procedure") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure conditionalExpressions {"
		"while(x == 2) {read x;}"
		"while(x != 2) {read x;}"
		"while(x < 2) {read x;}"
		"while(x <= 2) {read x;}"
		"while(x > 2) {read x;}"
		"while(x >= 2) {read x;}"
		"while(!(x == 2)) {read x;}"
		""
		"while(0 == 2147483647) {read x;}"
		"while(0 != 2147483647) {read x;}"
		"while(0 < 2147483647) {read x;}"
		"while(0 <= 2147483647) {read x;}"
		"while(0 > 2147483647) {read x;}"
		"while(0 >= 2147483647) {read x;}"
		"while(!(0 == 2147483647)) {read x;}"
		""
		"while((x == 2) && (x == 1)) {read x;}"
		"while((x != 2) || (x != 2)) {read x;}"
		"while((!(x == 2)) && (!(x == 1))) {read x;}"
		"while( ((x == 2) && (x == 1)) || (x == 3)) {read x;}"
		"while(!(!(!(!(!(!(!(!(!(!(x==3))))))))))) {read x;}"
		"while(((x <= y) || (!(y == z))) && (!(z >= x))) {read x;}"
		"}";
	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> ast = parser.parse();
	SimpleControlFlow cfg(ast);
	std::vector<std::shared_ptr<CFGNode>> cfgGraphs = *(cfg.createControlFlowGraphs());

	REQUIRE(cfgGraphs.size() == 1);

	auto& node = cfgGraphs[0];

	SECTION("Traversing while nodes") {
		for (int i = 0; i < 20; i++) {
			REQUIRE(node->getLineNumber() == 2 * i + 1);
			node = (node->getChildren())[0];
			REQUIRE(node->getLineNumber() == 2 * i + 2);
			node = (node->getChildren())[0];
			REQUIRE(node->getLineNumber() == 2 * i + 1);
			node = (node->getChildren())[1];
		}

		REQUIRE(node->getLineNumber() == -1);
	}
	std::filesystem::remove(filename);
}

TEST_CASE("CFG generation for multiple procedures, with all names that may be potential keywords.") {
	// Generate test file
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure assign { read x; }"
		"procedure call { read x; }"
		"procedure constant { read x; }"
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
	std::shared_ptr<ASTNode> ast = parser.parse();
	SimpleControlFlow cfg(ast);
	std::vector<std::shared_ptr<CFGNode>> cfgGraphs = *(cfg.createControlFlowGraphs());

	REQUIRE(cfgGraphs.size() == 30);

	for (int i = 0; i < cfgGraphs.size(); i++) {
		REQUIRE(cfgGraphs[i]->getLineNumber() == i + 1);
		REQUIRE(cfgGraphs[i]->getChildren()[0]->getLineNumber() == -1);
	}

	std::filesystem::remove(filename);
}

TEST_CASE("CFG generation for 20 nested while statements") {
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
		"read x;"
		"}}}}}}}}}}}}}}}}}}}}}";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> ast = parser.parse();
	SimpleControlFlow cfg(ast);
	std::vector<std::shared_ptr<CFGNode>> cfgGraphs = *(cfg.createControlFlowGraphs());

	SECTION("Traversing while nodes") {
		REQUIRE(cfgGraphs.size() == 1);

		auto& node = cfgGraphs[0];

		for (int i = 1; i <= 21; i++) {
			REQUIRE(node->getLineNumber() == i);
			node = (node->getChildren())[0];
		}

		for (int i = 20; i >= 1; i--) {
			REQUIRE(node->getLineNumber() == i);
			node = (node->getChildren())[1];
		}

		REQUIRE(node->getLineNumber() == -1);
	}
	std::filesystem::remove(filename);
}

TEST_CASE("CFG for complex nested if-while constructs") {
	std::string filename = "sample.txt";
	std::string sampleProgram = "procedure nestedIfWhile {"
		"while (x == y) {"			// 1
		"if (x == y) then {"		// 2
		"while (x > y) {"			// 3
		"read x;"					// 4
		"}"
		"while (y > x) {"			// 5
		"read y;"					// 6
		"}"
		"} else {"
		"if (x != y) then {"		// 7
		"while (!(x == y)) {"		// 8
		"read y;"					// 9
		"}"
		"} else {"
		"while (x >= y) {"			// 10
		"read y;"					// 11
		"}"
		"}"
		"if (x >= y) then {"		// 12
		"while(x <= y) {"			// 13
		"read y;"					// 14
		"}"
		"} else {"
		"while ((y > x) || (!(y == x))) {"	// 15
		"read y;"							// 16
		"}"
		"}"
		"}"
		"}"
		"}";

	std::ofstream file;
	file.open(filename);
	file << sampleProgram;
	file.close();
	REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> ast = parser.parse();
	SimpleControlFlow cfg(ast);
	std::vector<std::shared_ptr<CFGNode>> cfgGraphs = *(cfg.createControlFlowGraphs());

	REQUIRE(cfgGraphs.size() == 1);

	auto& node = cfgGraphs[0];

	SECTION("Check Complex Nested Constructs") {
		REQUIRE(node->getLineNumber() == 1);
		REQUIRE((node->getChildren())[1]->getLineNumber() == -1);

		node = (node->getChildren())[0];
		REQUIRE(node->getLineNumber() == 2);

		std::vector<std::shared_ptr<CFGNode>> ifElseStatement = node->getChildren();
		auto& ifBlockNode = ifElseStatement[0];
		auto& elseBlockNode = ifElseStatement[1];

		REQUIRE(ifBlockNode->getLineNumber() == 3);

		std::vector<std::shared_ptr<CFGNode>> whileStatement = ifBlockNode->getChildren();
		REQUIRE(whileStatement.size() == 2);

		REQUIRE(whileStatement[0]->getLineNumber() == 4);
		REQUIRE(whileStatement[1]->getLineNumber() == 5);

		whileStatement = whileStatement[1]->getChildren();
		REQUIRE(whileStatement.size() == 2);
		REQUIRE(whileStatement[0]->getLineNumber() == 6);
		REQUIRE(whileStatement[1]->getLineNumber() == 1);

		REQUIRE(elseBlockNode->getLineNumber() == 7);
		REQUIRE(elseBlockNode->getChildren().size() == 2);
		REQUIRE((elseBlockNode->getChildren()[0])->getLineNumber() == 8);

		whileStatement = elseBlockNode->getChildren()[0]->getChildren();
		REQUIRE(whileStatement.size() == 2);
		REQUIRE(whileStatement[0]->getLineNumber() == 9);
		REQUIRE(whileStatement[1]->getLineNumber() == 12);

		REQUIRE((elseBlockNode->getChildren()[1])->getLineNumber() == 10);
		whileStatement = elseBlockNode->getChildren()[1]->getChildren();
		REQUIRE(whileStatement.size() == 2);
		REQUIRE(whileStatement[0]->getLineNumber() == 11);
		REQUIRE(whileStatement[1]->getLineNumber() == 12);

		std::vector<std::shared_ptr<CFGNode>> secondNestedIfElseBlock = elseBlockNode->getChildren()[1]->getChildren()[1]->getChildren();
		REQUIRE(secondNestedIfElseBlock.size() == 2);

		auto& elseIfNode = secondNestedIfElseBlock[0];
		auto& elseElseNode = secondNestedIfElseBlock[1];

		REQUIRE(elseIfNode->getLineNumber() == 13);
		REQUIRE(elseIfNode->getChildren().size() == 2);
		REQUIRE((elseIfNode->getChildren()[0])->getLineNumber() == 14);
		REQUIRE((elseIfNode->getChildren()[1])->getLineNumber() == 1);

		REQUIRE(elseElseNode->getLineNumber() == 15);
		REQUIRE(elseElseNode->getChildren().size() == 2);
		REQUIRE((elseElseNode->getChildren()[0])->getLineNumber() == 16);
		REQUIRE((elseElseNode->getChildren()[1])->getLineNumber() == 1);
	}
	std::filesystem::remove(filename);
}
