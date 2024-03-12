#include "sp/DesignExtractor/DesignExtractorFacade.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"
#include "sp/AST/ASTUtility.h"
#include "catch.hpp"
#include <unordered_set>
#include <vector>


TEST_CASE("sp/SourceProcessor: Follow(unit)") {
	std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
	std::shared_ptr<FollowsReader> followsReader = pkbManager->getPKBReaderManager()->getFollowsReader();
	std::shared_ptr<FollowsTReader> followsTReader = pkbManager->getPKBReaderManager()->getFollowsTReader();

	SECTION("Basic Parent") {
		SECTION("Test Parent") {
			std::shared_ptr<ASTNode> ast1 = std::make_shared<ASTNode>(ASTNodeType::IF_ELSE_THEN, 1, "ifs");
			std::shared_ptr<ASTNode> ast2 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 2, "x");
			FollowsExtractor followsExtractor(ast1, ast2, pkbWriterManager->getFollowsWriter());
			followsExtractor.extract();
			std::unordered_set<int> expected = { 2 };
			REQUIRE(followsReader->getPostFollows(1) == expected);
		}

		SECTION("Test ParentT") {
			std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::WHILE, 3, "whiles");
			std::shared_ptr<ASTNode> ast4 = std::make_shared<ASTNode>(ASTNodeType::PRINT, 6, "print");
			FollowsTExtractor followsExtractor(ast3, ast4, pkbWriterManager->getFollowsTWriter());
			followsExtractor.extract();
			std::unordered_set<int> expected = { 3 };
			REQUIRE(followsTReader->getPreFollowsT(6) == expected);
		}
	}
}