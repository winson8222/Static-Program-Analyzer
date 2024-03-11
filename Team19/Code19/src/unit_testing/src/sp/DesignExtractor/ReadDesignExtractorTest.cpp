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

TEST_CASE("sp/DesignExtractor/Visitor/ReadVisitor") {
	std::shared_ptr<ASTNode> read1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::READ, 2, "read"));
	read1->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x")));

	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	SECTION("Valid read initializations") {
		REQUIRE_NOTHROW(ReadExtractor(read1, pkbWriterManager->getReadWriter()));
	}

	SECTION("Invalid print statement") {
		std::shared_ptr<ASTNode> read2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PRINT, 2, "read"));
		auto context = std::vector<std::shared_ptr<ASTNode>>{ read2 };
		REQUIRE_THROWS(ReadVisitor(read2, context, pkbWriterManager));
	}
}

TEST_CASE("sp/DesignExtractor/Extractor/ReadExtractor") {
	/*
	procedure proc1 {
		read x;
		read y;
		read z;
	}
	*/
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode());
	std::shared_ptr<ASTNode> proc1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::PROCEDURE, 1, "proc1"));
	std::shared_ptr<ASTNode> stmtLst1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::STATEMENT_LIST, 1, "stmtLst1"));
	std::shared_ptr<ASTNode> read1 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::READ, 2, "READ"));
	std::shared_ptr<ASTNode> read2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::READ, 3, "READ"));
	std::shared_ptr<ASTNode> read3 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::READ, 4, "READ"));
	read1->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 2, "x")));
	read2->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 3, "y")));
	read3->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 4, "z")));
	stmtLst1->addChild(read1);
	stmtLst1->addChild(read2);
	stmtLst1->addChild(read3);
	proc1->addChild(stmtLst1);
	root->addChild(proc1);

	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	DesignExtractorFacade fde(root, pkbWriterManager);

	SECTION("Valid read initializations") {
		REQUIRE_NOTHROW(fde.extractAll());
	}
	fde.extractAll();
	std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();

	SECTION("Extract all reads") {
		std::unordered_set<int> expectedReads = { 2, 3, 4 };
		auto actualReads = pkbReaderManager->getReadReader()->getAllReads();
		REQUIRE(expectedReads == actualReads);
	}

	SECTION("Extract all read variables") {
		std::unordered_set<std::string> expectedReadVars = { "x", "y", "z" };
		auto actualReadVars = pkbReaderManager->getVariableReader()->getAllVariables();
		REQUIRE(expectedReadVars == actualReadVars);
	}
}
