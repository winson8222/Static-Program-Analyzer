#include "catch.hpp"
#include <iostream>
#include <filesystem>
#include <fstream>
#include "sp/ControlFlow/SimpleControlFlow.h"
#include "sp/Parser/SimpleParserFacade.h"

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
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();
	SimpleControlFlow controlFlow = SimpleControlFlow(tree_ptr);
	std::vector<std::shared_ptr<CFGNode>> cfg = *(controlFlow.createControlFlowGraphs());

	SECTION("Check children number") {
		REQUIRE(cfg.size() == 2);

		auto& node = cfg[0];

		SECTION("Check procedures") {
			for (int i = 1; i <= 4; i++) {
				REQUIRE(node->getLineNumber() == i);
				node = (node->getChildren())[0];
			}

			REQUIRE(node->getLineNumber() == 5);

			node = (node->getChildren())[1];
			REQUIRE(node->getLineNumber() == 6);

			node = (node->getChildren())[0];
			REQUIRE(node->getLineNumber() == 5);

			node = (node->getChildren())[0];
			REQUIRE(node->getLineNumber() == 7);

			std::vector<std::shared_ptr<CFGNode>> ifElseStatement = node->getChildren();
			auto& ifBlockNode = ifElseStatement[0];
			auto& elseBlockNode = ifElseStatement[1];

			REQUIRE(ifBlockNode->getLineNumber() == 8);
			REQUIRE((ifBlockNode->getChildren()[0])->getLineNumber() == -1);

			REQUIRE(elseBlockNode->getLineNumber() == 9);
			REQUIRE((elseBlockNode->getChildren()[0])->getLineNumber() == -1);
		}

		node = cfg[1];
		SECTION("Check second procedure") {
			REQUIRE(node->getLineNumber() == 10);
			REQUIRE((node->getChildren()[0])->getLineNumber() == -1);
		}
	}
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
	SimpleControlFlow controlFlow = SimpleControlFlow(parser.parse());
	std::vector<std::shared_ptr<CFGNode>> cfg = *(controlFlow.createControlFlowGraphs());

	SECTION("Traversing while nodes") {
		REQUIRE(cfg.size() == 1);

		auto& node = cfg[0];

		for (int i = 1; i <= 20; i++) {
			REQUIRE(node->getLineNumber() == i);
			node = (node->getChildren())[1];
		}

		for (int i = 21; i >= 1; i--) {
			REQUIRE(node->getLineNumber() == i);
			node = (node->getChildren())[0];
		}


		REQUIRE(node->getLineNumber() == -1);
	}
}
