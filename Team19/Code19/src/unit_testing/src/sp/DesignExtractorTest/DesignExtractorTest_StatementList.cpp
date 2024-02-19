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
