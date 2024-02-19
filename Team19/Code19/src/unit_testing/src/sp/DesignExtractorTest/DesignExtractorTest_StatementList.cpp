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
	std::cout << "BEGIN DESIGN EXTRACTOR TEST FOR STATEMENT LISTS" << std::endl;
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode());
	std::shared_ptr<ASTNode> prog = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROGRAMS, 0, "prog"));
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));


	proc1->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 1, "statement lists")));
	prog->addChild(proc1);
	root->addChild(prog);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	FDesignExtractor fde(root, pkbWriterManager);
	REQUIRE_NOTHROW(fde.extractAll());

	std::cout << "END DESIGN EXTRACTOR TEST FOR LISTS" << std::endl;
}
