#include "sp/DesignExtractor/DesignExtractorFacade.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"
#include "sp/AST/ASTUtility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <vector>


TEST_CASE("sp/DesignExtractor/Extractor/ProcedureExtractor") {
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode());
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));
	std::shared_ptr<ASTNode> proc2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 2, "proc2"));

	root->addChild(proc1);
	root->addChild(proc2);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	DesignExtractorFacade fde(root, pkbWriterManager);

	SECTION("Valid procedure initializations") {
		REQUIRE_NOTHROW(fde.extractAll());
	}
	
	fde.extractAll();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();

	SECTION("Extract all procedures") {
		std::unordered_set<std::string> expectedProcNames = { "proc1", "proc2"};
		auto val = pkbReaderManager->getProcedureReader()->getAllProcedures();
		REQUIRE(val == expectedProcNames);
	}
}

TEST_CASE("sp/DesignExtractor/Visitor/ProcedureVisitor") {
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 0, "proc"));
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));

	root->addChild(proc1);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
}
