#include "sp/DesignExtractor/DesignExtractorFacade.h"
#include "sp/AST/ASTNode.h"
#include "sp/Parser/SimpleParserFacade.h"
#include "pkb/PKBManager.h"
#include "sp/AST/ASTUtility.h"
#include "catch.hpp"
#include <filesystem>
#include <unordered_set>
#include <vector>


TEST_CASE("sp/SourceProcessor: Parent(unit)") {
    std::shared_ptr<PKBManager> pkbManager = std::make_shared<PKBManager>();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager->getPKBWriterManager();
    std::shared_ptr<ParentReader> parentReader = pkbManager->getPKBReaderManager()->getParentReader();
    std::shared_ptr<ParentTReader> parentTReader = pkbManager->getPKBReaderManager()->getParentTReader();

    SECTION("Basic Parent") {
        SECTION("Test Parent") {
			std::shared_ptr<ASTNode> ast1 = std::make_shared<ASTNode>(ASTNodeType::IF_ELSE_THEN, 1, "ifs");
			std::shared_ptr<ASTNode> ast2 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 2, "x");
			ParentExtractor parentExtractor1(ast1, ast2, pkbWriterManager);
			parentExtractor1.extract();
			std::unordered_set<int> expected = {1};
			REQUIRE(parentReader->getAllParents() == expected);
			REQUIRE(parentReader->getParent(2) == expected);
		}
		
		SECTION("Test ParentT") {
			std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::IF_ELSE_THEN, 3, "ifs");
			std::shared_ptr<ASTNode> ast4 = std::make_shared<ASTNode>(ASTNodeType::PRINT, 6, "print");
			ParentTExtractor parentExtractor2(ast3, ast4, pkbWriterManager);
			parentExtractor2.extract();
			std::unordered_set<int> expected = { 3 };
			REQUIRE(parentTReader->getAllParentTs() == expected);
			REQUIRE(parentTReader->getParentT(6) == expected);
		}
    }
}