#include "sp/DesignExtractor/DesignExtractorFacade.h"
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


TEST_CASE("Tests for assign statements", "[DesignExtractor::extract]") {
	const std::string testFileName = "../../../../../tests/sp/DesignExtractorTest/assign1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> root = parser.parse();
	
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	DesignExtractorFacade fde(root, pkbWriterManager);

	SECTION("Test for assign statement") {
		fde.extractAll();
		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();

		std::unordered_set<int> expectedAssigns = {2, 3};
		std::unordered_set<int> expectedStmts = {2, 3};
		REQUIRE(pkbReaderManager->getAssignReader()->getAllAssigns() == expectedAssigns);
		REQUIRE(pkbReaderManager->getStatementReader()->getAllStatements() == expectedStmts);
		std::unordered_set<std::string> expectedVars = {"x", "y", "z"};
		REQUIRE(pkbReaderManager->getVariableReader()->getAllVariables() == expectedVars);
	}
}