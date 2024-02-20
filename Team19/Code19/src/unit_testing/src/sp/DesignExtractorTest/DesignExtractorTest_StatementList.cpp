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


TEST_CASE("Tests for DesignExtractors for Statement Lists", "[DesignExtractor::extract]") {
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode());
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));


	proc1->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 1, "statement lists")));
	root->addChild(proc1);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	FDesignExtractor fde(root, pkbWriterManager);
	REQUIRE_NOTHROW(fde.extractAll());
}

TEST_CASE("Tests for statement extractors", "[DesignExtractor::extract]") {
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode());
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));

	std::shared_ptr<ASTNode> stmtLst = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 1, "statement lists"));
	
	std::shared_ptr<ASTNode> print1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PRINT, 2, "print"));
	print1->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x")));
	std::shared_ptr<ASTNode> print2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PRINT, 3, "print"));
	print2->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 3, "y")));
	std::shared_ptr<ASTNode> read1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::READ, 4, "read"));
	read1->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 4, "x"));
	std::shared_ptr<ASTNode> read2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::READ, 5, "read"));
	read2->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 5, "y"));

	stmtLst->addChild(print1);
	stmtLst->addChild(print2);
	stmtLst->addChild(read1);
	stmtLst->addChild(read2);

	proc1->addChild(stmtLst);
	root->addChild(proc1);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	FDesignExtractor fde(root, pkbWriterManager);
	REQUIRE_NOTHROW(fde.extractAll());

	std::unordered_set<int> expected = { 2, 3, 4, 5 };
	std::unordered_set<int> actual = pkb->getPKBReaderManager()->getStatementReader()->getAllStatements();

	REQUIRE(expected == actual);
}

TEST_CASE("Tests invalid DesignExtractors for Statement Lists", "[DesignExtractor::extract]") {
	std::cout << "INVALID STATEMENT LIST" << std::endl;
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode());
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));

	auto statementList = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 1, "statement lists"));
	statementList->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::DIVIDE, 2, "add")));

	proc1->addChild(statementList);
	root->addChild(proc1);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();

	std::cout << root->toString() << std::endl;
	FDesignExtractor fde(root, pkbWriterManager);
	REQUIRE_THROWS_WITH(fde.extractAll(), "ERROR: Not a statement!");
}
