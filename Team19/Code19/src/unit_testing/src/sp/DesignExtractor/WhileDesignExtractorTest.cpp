#include "sp/DesignExtractor/DesignExtractorFacade.h"
#include "sp/AST/ASTNode.h"
#include "sp/Parser/SimpleParserFacade.h"
#include "pkb/PKBManager.h"
#include "sp/AST/ASTUtility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <vector>



TEST_CASE("While extract singular") {
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();

	std::shared_ptr<ASTNode> whileNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::WHILE, 2, "while"));
	WhileExtractor whileExtractor(whileNode, pkbWriterManager->getWhileWriter());
	whileExtractor.extract();
	std::unordered_set<int> expectedWhiles = { 2 };

	SECTION("Extract while") {
		auto whiles = pkbReaderManager->getWhileReader()->getAllWhiles();
		REQUIRE(whiles == expectedWhiles);
	}
}

TEST_CASE("sp/DesignExtractor/Extractor/WhileExtract") {
	/*
	procedure proc1 {
		while (x < 4) {
			print y;
		}
	}
	*/
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode());
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));
	std::shared_ptr<ASTNode> stmtLst1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 1, "stmtLst1"));
	std::shared_ptr<ASTNode> whileNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::WHILE, 2, "while"));
	std::shared_ptr<ASTNode> var1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x"));
	std::shared_ptr<ASTNode> relExprNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::LESSER, 2, "<"));
	std::shared_ptr<ASTNode> const1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::CONSTANT, 2, "4"));
	relExprNode->addChild(var1);
	relExprNode->addChild(const1);
	whileNode->addChild(relExprNode);
	std::shared_ptr<ASTNode> stmtLst = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 2, "stmtLst"));
	std::shared_ptr<ASTNode> printNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PRINT, 3, "print"));
	std::shared_ptr<ASTNode> var2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 3, "y"));
	printNode->addChild(var2);
	stmtLst->addChild(printNode);
	whileNode->addChild(stmtLst);
	stmtLst1->addChild(whileNode);
	proc1->addChild(stmtLst1);
	root->addChild(proc1);

	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	DesignExtractorFacade fde(root, pkbWriterManager);

	SECTION("Valid while initializations") {
		REQUIRE_NOTHROW(fde.extractAll());
	}
	
	fde.extractAll();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();

	SECTION("Extract all whiles") {
		auto whiles = pkbReaderManager->getWhileReader()->getAllWhiles();
		std::unordered_set<int> expectedWhiles = { 2 };
		REQUIRE(whiles == expectedWhiles);
	}

	SECTION("Extract all statements") {
		auto whiles = pkbReaderManager->getStatementReader()->getAllStatements();
		std::unordered_set<int> expectedWhiles = { 2, 3 };
		REQUIRE(whiles == expectedWhiles);
	}

	SECTION("Extract all variables") {
		std::unordered_set<std::string> expectedVars = { "x", "y" };
		auto val = pkbReaderManager->getVariableReader()->getAllVariables();
		REQUIRE(val == expectedVars);
	}

	SECTION("Extract all constants") {
		std::unordered_set<int> expectedConsts = { 4 };
		auto consts = pkbReaderManager->getConstantReader()->getAllConstants();
		REQUIRE(consts == expectedConsts);
	}


}

TEST_CASE("sp/DesignExtractor/Visitor/WhileVisitor") {
	std::shared_ptr<ASTNode> whileNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::WHILE, 2, "while"));
	std::shared_ptr<ASTNode> var1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x"));
	std::vector<std::shared_ptr<ASTNode>> children;
	whileNode->addChild(var1);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();

	SECTION("Invalid while initializations") {
		std::shared_ptr<ASTNode> relExprNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::LESSER, 2, "<"));
		REQUIRE_THROWS_WITH(WhileVisitor(relExprNode, children, pkbWriterManager),
			"ERROR: Cannot initialized a non-WHILE node");
	}
}