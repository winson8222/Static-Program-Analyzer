#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"
#include "sp/AST/ASTUtility.h"
#include "sp/DesignExtractor/Visitor/VariableVisitor.h"
#include "catch.hpp"
#include <fstream>
#include <unordered_set>
#include <vector>

TEST_CASE("sp/DesignExtractor/Extractor/VariableExtractor") {
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	std::shared_ptr<ASTNode> variable = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 1, "x"));

	VariableExtractor constantExtractor(variable, pkbWriterManager);
	constantExtractor.extract();
	SECTION("Test constant extractor methods") {
		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();
		std::unordered_set<std::string> expectedVariables = { "x" };
		REQUIRE(pkbReaderManager->getVariableReader()->getAllVariables() == expectedVariables);
	}
}

TEST_CASE("sp/DesignExtractor/Extractor/VariableVisitor") {
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	std::shared_ptr<ASTNode> variable = std::make_shared<ASTNode>(ASTNode(ASTNodeType::VARIABLE, 1, "x"));

	std::vector<std::shared_ptr<ASTNode>> usedContexts;
	std::vector<std::shared_ptr<ASTNode>> modifiedContexts;
	usedContexts.push_back(std::make_shared<ASTNode>(ASTNode(ASTNodeType::ASSIGN, 2, "x")));
	modifiedContexts.push_back(std::make_shared<ASTNode>(ASTNodeType::IF_ELSE_THEN, 3, "x"));

	VariableVisitor variableVisitor(variable, pkbWriterManager);
	variableVisitor.setUsedContext(usedContexts, variable);
	variableVisitor.setModifiedContext(modifiedContexts, variable);
	variableVisitor.visit();

	SECTION("Test variable visitor methods") {
		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();
		std::unordered_set<std::string> expectedVariables = { "x" };
		REQUIRE(pkbReaderManager->getVariableReader()->getAllVariables() == expectedVariables);
		REQUIRE(pkbReaderManager->getUsesSReader()->getAllStmtsThatUseVariable("x") == std::unordered_set<int>({ 2 }));
		REQUIRE(pkbReaderManager->getModifiesSReader()->getAllStmtsThatModifyVariable("x") == std::unordered_set<int>({ 3 }));
	}

	// to add call test later here
}