#include "sp/DesignExtractor/DesignExtractorFacade.h"
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


TEST_CASE("sp/DesignExtractor/Visitor/IfElseThenExtractor") {
	/// <summary>
	/// set up for procedure proc1 { if (x < 4) then { print y; } else {read z; }}
	/// </summary>
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode());
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));
	std::shared_ptr<ASTNode> stmtLst = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 1, "stmtLst1"));
	std::shared_ptr<ASTNode> ifNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::IF_ELSE_THEN, 2, "while"));
	std::shared_ptr<ASTNode> var1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x"));
	std::shared_ptr<ASTNode> relExprNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::LESSER, 2, "<"));
	std::shared_ptr<ASTNode> const1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::CONSTANT, 2, "4"));
	relExprNode->addChild(var1);
	relExprNode->addChild(const1);
	ifNode->addChild(relExprNode);
	std::shared_ptr<ASTNode> stmtLst1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 2, "stmtLst"));
	std::shared_ptr<ASTNode> stmtLst2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 4, "stmtLst"));
	std::shared_ptr<ASTNode> printNode1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PRINT, 3, "print"));
	std::shared_ptr<ASTNode> var2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 3, "y"));
	std::shared_ptr<ASTNode> readNode1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::READ, 5, "read"));
	std::shared_ptr<ASTNode> var3 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 5, "z"));
	printNode1->addChild(var2);
	readNode1->addChild(var3);
	stmtLst1->addChild(printNode1);
	stmtLst2->addChild(readNode1);
	ifNode->addChild(stmtLst1);
	ifNode->addChild(stmtLst2);
	stmtLst->addChild(ifNode);
	proc1->addChild(stmtLst);
	root->addChild(proc1);

	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	DesignExtractorFacade fde(root, pkbWriterManager);

	SECTION("Test valid ifs extraction and initializations") {
		REQUIRE_NOTHROW(fde.extractAll());
	}

	fde.extractAll();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();

	SECTION("Test valid variable retrieve") {
		std::unordered_set<std::string> expectedVariables = { "x", "y", "z" };
		REQUIRE(pkbReaderManager->getVariableReader()->getAllVariables() == expectedVariables);
	}

	SECTION("Test valid constant retrieve") {
		std::unordered_set<int> expectedConstants = { 4 };
		REQUIRE(pkbReaderManager->getConstantReader()->getAllConstants() == expectedConstants);

	}

	SECTION("Test valid if retrieve") {
		std::unordered_set<int> expectedIfs = { 2 };
		REQUIRE(pkbReaderManager->getIfReader()->getAllIfs() == expectedIfs);

	}

	SECTION("Test valid statement retrieve") {
		std::unordered_set<int> expectedStatements = { 2, 3, 5 };
		REQUIRE(pkbReaderManager->getStatementReader()->getAllStatements() == expectedStatements);

	}
}

TEST_CASE("sp/DesignExtractor/Visitor/IfElseThenVisitor") {
	SECTION("Test valid If initializations") {
		std::shared_ptr<ASTNode> ifNodes = std::make_shared<ASTNode>(ASTNode(ASTNodeType::IF_ELSE_THEN, 2, "ifs"));
		std::shared_ptr<ASTNode> var1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x"));
		std::vector<std::shared_ptr<ASTNode>> children;
		ifNodes->addChild(var1);
		ifNodes->addChild(var1);
		ifNodes->addChild(var1);
		std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
		std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
		REQUIRE_NOTHROW(IfElseThenVisitor(ifNodes, children, pkbWriterManager));
	}

	std::shared_ptr<ASTNode> ifNodes = std::make_shared<ASTNode>(ASTNode(ASTNodeType::IF_ELSE_THEN, 2, "ifs"));
	std::shared_ptr<ASTNode> var1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x"));
	std::vector<std::shared_ptr<ASTNode>> children;
	ifNodes->addChild(var1);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	SECTION("Test invalid size of IF children") {
		REQUIRE_THROWS_WITH(IfElseThenVisitor(ifNodes, children, pkbWriterManager),
			"ERROR: IfElseThenVisitor - input root does not have 3 children");
	}

	
	SECTION("Test invalid root of IF node") {
		std::shared_ptr<ASTNode> relExprNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::LESSER, 2, "<"));
		REQUIRE_THROWS_WITH(IfElseThenVisitor(relExprNode, children, pkbWriterManager),
			"ERROR: IfElseThenVisitor - input root is not of type ASTNodeType::IF_ELSE_THEN");
	}
}