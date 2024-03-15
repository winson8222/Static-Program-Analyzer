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
	std::shared_ptr<ASTNode> stmtLst1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 1, "a"));
	std::shared_ptr<ASTNode> stmtLst2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 2, "b"));
	std::shared_ptr<ASTNode> print1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PRINT, 2, "print"));
	print1->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x")));
	std::shared_ptr<ASTNode> print2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PRINT, 3, "print"));
	print2->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 3, "y")));
	stmtLst1->addChild(print1);
	stmtLst2->addChild(print2);
	proc1->addChild(stmtLst1);
	proc2->addChild(stmtLst2);
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

	SECTION("Extract procedure singular") {
		std::shared_ptr<ASTNode> proc = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 3, "proc3"));
		ProcedureExtractor procExtractor(proc, pkbWriterManager->getProcedureWriter());
		REQUIRE_NOTHROW(procExtractor.extract());

		std::unordered_set<std::string> expectedProcNames = { "proc1", "proc2", "proc3" };
		auto val = pkbReaderManager->getProcedureReader()->getAllProcedures();
		REQUIRE(val == expectedProcNames);
	}
}

TEST_CASE("sp/DesignExtractor/Visitor/ProcedureVisitor") {
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>();
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));
	std::shared_ptr<ASTNode> stmtLst1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 1, "a"));
	std::shared_ptr<ASTNode> print1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PRINT, 1, "print"));
	print1->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 1, "x")));
	stmtLst1->addChild(print1);
	proc1->addChild(stmtLst1);
	root->addChild(proc1);

	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	ProcedureVisitor visitor(proc1, pkbWriterManager);
	REQUIRE_NOTHROW(visitor.visit());

	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();
	std::unordered_set<std::string> expectedProcNames = { "proc1" };
	auto val = pkbReaderManager->getProcedureReader()->getAllProcedures();
	REQUIRE(val == expectedProcNames);

	std::unordered_set<int> expectedNext = {};
	auto val2 = pkbReaderManager->getNextReader()->getAllNext();
	REQUIRE(val2 == expectedNext);
}
