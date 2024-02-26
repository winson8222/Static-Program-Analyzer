#include "sp/DesignExtractor/DesignExtractorFacade.h"
#include "sp/DesignExtractor/Extractor/ConstantExtractor.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"
#include "sp/AST/ASTUtility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <vector>

TEST_CASE("sp/DesignExtractor/Extractor/ConstantExtractor") {
	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	std::shared_ptr<ASTNode> constant = std::make_shared<ASTNode>(ASTNode(ASTNodeType::CONSTANT, 1, "1"));

	ConstantExtractor constantExtractor(constant, pkbWriterManager);
	constantExtractor.extract();
	SECTION("Test constant extractor methods") {
		std::shared_ptr<PKBReaderManager> pkbReaderManager = pkb->getPKBReaderManager();
		std::unordered_set<int> expectedConstants = { 1 };
		REQUIRE(pkbReaderManager->getConstantReader()->getAllConstants() == expectedConstants);
	}
}