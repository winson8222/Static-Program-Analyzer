#include "sp/DesignExtractor/Extractor/VariableExtractor.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"
#include "sp/AST/ASTUtility.h"
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