#include "sp/DesignExtractor/DesignExtractorFacade.h"
#include "sp/AST/ASTNode.h"
#include "sp/Parser/SimpleParserFacade.h"
#include "pkb/PKBManager.h"
#include "sp/AST/ASTUtility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <vector>


TEST_CASE("sp/DesignExtractor/Visitor/AssignVisitor") {
	// scenario: x = y + z;
	std::shared_ptr<ASTNode> root = std::make_shared<ASTNode>(ASTNode(ASTNodeType::ASSIGN, 1, "assign"));
	root->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 1, "x")));
	auto expr = std::make_shared<ASTNode>(ASTNode(ASTNodeType::ADD, 1, "+"));
	expr->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 1, "y")));
	expr->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 1, "z")));
	root->addChild(expr);
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	std::vector<std::shared_ptr<ASTNode>> context;

	SECTION("Test assign visitor methods"){
		AssignVisitor assignVisitor1(root, context, pkbWriterManager);
		REQUIRE_NOTHROW(assignVisitor1.visit());

		auto root2 = std::make_shared<ASTNode>(ASTNode(ASTNodeType::ADD, 1, "add"));
		REQUIRE_THROWS(assignVisitor1 = AssignVisitor(root2, context, pkbWriterManager));
	}
}

TEST_CASE("sp/DesignExtractor/Extractor/AssignExtractor") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure proc1 {"
                                "x = y + z;"
                                "y = 2;"
                                "z = x + y * x - 2/2 + z;"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
	SimpleParserFacade parser(filename);
	std::shared_ptr<ASTNode> root = parser.parse();
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	DesignExtractorFacade fde(root, pkbWriterManager);

	SECTION("Test assign extractor methods") {
		fde.extractAll();
		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();
		std::unordered_set<int> expectedAssigns = { 1, 2, 3 };
		std::unordered_set<int> expectedStmts = { 1, 2, 3 };
		REQUIRE(pkbReaderManager->getAssignReader()->getAllAssigns() == expectedAssigns);
		REQUIRE(pkbReaderManager->getStatementReader()->getAllStatements() == expectedStmts);
		std::unordered_set<std::string> expectedVars = { "x", "y", "z" };
		REQUIRE(pkbReaderManager->getVariableReader()->getAllVariables() == expectedVars);
	}
    std::filesystem::remove(filename);

	SECTION("Test assign extractor modular") {
		std::shared_ptr<ASTNode> variable = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 1, "x"));
		REQUIRE_THROWS(AssignExtractor(variable, pkbWriterManager->getAssignWriter()));

		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();
		std::shared_ptr<ASTNode> assign = std::make_shared<ASTNode>(ASTNode(ASTNodeType::ASSIGN, 1, "assign"));
		AssignExtractor assignExtractor(assign, pkbWriterManager->getAssignWriter());
		assignExtractor.extract();

		std::unordered_set<int> expectedAssigns = { 1 };
		REQUIRE(pkbReaderManager->getAssignReader()->getAllAssigns() == expectedAssigns);
	}

	SECTION("Test assign pattern extractor modular") {
		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();
		std::shared_ptr<ASTNode> assign = std::make_shared<ASTNode>(ASTNode(ASTNodeType::ASSIGN, 1, "assign"));
		assign->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 1, "x")));
		assign->addChild(std::make_shared<ASTNode>(ASTNode(ASTNodeType::CONSTANT, 1, "0")));
		AssignPatternExtractor assignPatternExtractor(assign, assign->getChildByIndex(0), assign->getChildByIndex(1), pkbWriterManager->getAssignPatternWriter());
		REQUIRE_NOTHROW(assignPatternExtractor.extract());
	}
}