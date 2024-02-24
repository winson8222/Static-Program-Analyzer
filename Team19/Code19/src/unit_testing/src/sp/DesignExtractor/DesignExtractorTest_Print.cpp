#include "sp/DesignExtractor/DesignExtractorFacade.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"
#include "sp/Utility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <vector>

TEST_CASE("sp/DesignExtractor/Extractor/PrintExtractor") {
	std::shared_ptr<ASTNode> print1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PRINT, 2, "print"));
	print1->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x")));

	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	SECTION("Valid print initializations") {
		REQUIRE_NOTHROW(PrintExtractor(print1, pkbWriterManager));
	}

	SECTION("Invalid print statement") {
		std::shared_ptr<ASTNode> print2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::READ, 2, "read"));
		auto context = std::vector<std::shared_ptr<ASTNode>>{ print2 };
		REQUIRE_THROWS(PrintVisitor(print2, context, pkbWriterManager));
	}
}

TEST_CASE("sp/DesignExtractor/Visitor/PrintExtractor") {
	/*
	procedure proc1 {
		print x;
		print y;
	}
	*/
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode());
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));
	std::shared_ptr<ASTNode> stmtLst1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 1, "stmtLst1"));
	std::shared_ptr<ASTNode> print1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PRINT, 2, "print"));
	std::shared_ptr<ASTNode> print2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PRINT, 3, "print"));
	print1->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x")));
	print2->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 3, "y")));
	stmtLst1->addChild(print1);
	stmtLst1->addChild(print2);
	proc1->addChild(stmtLst1);
	root->addChild(proc1);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	DesignExtractorFacade fde(root, pkbWriterManager);

	SECTION("Extract all") {
		REQUIRE_NOTHROW(fde.extractAll());
	}

	fde.extractAll();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();

	SECTION("Extract print statements") {
		std::unordered_set<int> expectedPrints = { 2, 3 };
		auto actualPrints = pkbReaderManager->getPrintReader()->getAllPrints();
		REQUIRE(expectedPrints == actualPrints);
	}
	
	SECTION("Extract all statements") {
		std::unordered_set<int> expectedStatements = { 2, 3 };
		auto actualStatements = pkbReaderManager->getStatementReader()->getAllStatements();
		REQUIRE(expectedStatements == actualStatements);
	}

	SECTION("Extract all variables") {
		std::unordered_set<std::string> expectedVars = { "x", "y" };
		auto actualVars = pkbReaderManager->getVariableReader()->getAllVariables();
		REQUIRE(expectedVars == actualVars);
	}
}
