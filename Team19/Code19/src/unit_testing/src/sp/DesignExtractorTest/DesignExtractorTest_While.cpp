#include "sp/DesignExtractor/FacadeDesignExtractor.h"
#include "sp/AST/ASTNode.h"
#include "sp/Parser/SimpleParserFacade.h"
#include "pkb/PKBManager.h"
#include "sp/Utility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <vector>


TEST_CASE("Tests for while statements", "[DesignExtractor::extract]") {
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode());
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));

	/*
	procedure proc1 {
		while (x < 4) {
			print y;
		}
	}
	*/
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
	FDesignExtractor fde(root, pkbWriterManager);
	REQUIRE_NOTHROW(fde.extractAll());

	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();
    std::unordered_set<std::string> expectedVars = { "x", "y" };
	std::unordered_set<int> expectedConsts = { 4 };

	auto val = pkbReaderManager->getVariableReader()->getAllVariables();
	REQUIRE(val == expectedVars);
	auto consts = pkbReaderManager->getConstantReader()->getAllConstants();
	REQUIRE(consts == expectedConsts);

	auto whiles = pkbReaderManager->getWhileReader()->getAllWhiles();
	std::unordered_set<int> expectedWhiles = { 2 };
	REQUIRE(whiles == expectedWhiles);
}

TEST_CASE("Tests invalid while statements", "[DesignExtractor::extract]") {
	std::shared_ptr<ASTNode> whileNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::WHILE, 2, "while"));
	std::shared_ptr<ASTNode> var1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x"));

	whileNode->addChild(var1);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();

	REQUIRE_THROWS_WITH(WhileVisitor(whileNode, pkbWriterManager),
		"ERROR: While node is not correct");

	std::shared_ptr<ASTNode> relExprNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::LESSER, 2, "<"));
	REQUIRE_THROWS_WITH(WhileVisitor(relExprNode, pkbWriterManager),
		"ERROR: Cannot initialized a non-WHILE node");
}