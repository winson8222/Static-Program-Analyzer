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


TEST_CASE("Tests for if-then-else statements", "[DesignExtractor::extract]") {
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

	std::cout << root->toString() << std::endl;

	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	FDesignExtractor fde(root, pkbWriterManager);
	REQUIRE_NOTHROW(fde.extractAll());

	std::unordered_set<std::string> expectedVariables = { "x", "y", "z" };
	std::unordered_set<int> expectedConstants = { 4 };
	std::unordered_set<int> expectedIfs = { 2 };
	std::unordered_set<int> expectedStatements = { 2, 3, 5 };

	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();

	REQUIRE(pkbReaderManager->getVariableReader()->getAllVariables() == expectedVariables);
	REQUIRE(pkbReaderManager->getConstantReader()->getAllConstants() == expectedConstants);
	REQUIRE(pkbReaderManager->getIfReader()->getAllIfs() == expectedIfs);
	REQUIRE(pkbReaderManager->getStatementReader()->getAllStatements() == expectedStatements);
}

TEST_CASE("Tests for INVALID if-then-else statements", "[DesignExtractor::extract]") {
	std::shared_ptr<ASTNode> ifNodes = std::make_shared<ASTNode>(ASTNode(ASTNodeType::IF_ELSE_THEN, 2, "while"));
	std::shared_ptr<ASTNode> var1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x"));

	std::vector<std::shared_ptr<ASTNode>> children;

	ifNodes->addChild(var1);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();

	REQUIRE_THROWS_WITH(IfElseThenVisitor(ifNodes, children, pkbWriterManager),
		"ERROR: IfElseThenVisitor - input root does not have 3 children");

	std::shared_ptr<ASTNode> relExprNode = std::make_shared<ASTNode>(ASTNode(ASTNodeType::LESSER, 2, "<"));
	REQUIRE_THROWS_WITH(IfElseThenVisitor(relExprNode, children, pkbWriterManager),
		"ERROR: IfElseThenVisitor - input root is not of type ASTNodeType::IF_ELSE_THEN");
}