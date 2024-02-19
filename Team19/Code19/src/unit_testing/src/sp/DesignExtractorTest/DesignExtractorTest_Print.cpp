#include "sp/DesignExtractor/FacadeDesignExtractor.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"
#include "sp/Utility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <vector>


TEST_CASE("Tests for DesignExtractors for Print", "[DesignExtractor::extract]") {

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
	FDesignExtractor fde(root, pkbWriterManager);
	REQUIRE_NOTHROW(fde.extractAll());

	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();

	std::unordered_set<int> expectedPrints = { 2, 3 };
	std::unordered_set<std::string> expectedPrintVars = { "x", "y" };

	auto actualPrints = pkbReaderManager->getPrintReader()->getAllPrints();
	auto actualPrintVars = pkbReaderManager->getVariableReader()->getAllVariables();

	REQUIRE(expectedPrints == actualPrints);
	REQUIRE(expectedPrintVars == actualPrintVars);
}
