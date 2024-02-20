#include "sp/DesignExtractor/FacadeDesignExtractor.h"
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

TEST_CASE("Test whiles integrating with parsers", "[DesignExtractor::Whiles]") {
	const std::string testFileName = "../../../../../tests/sp/DesignExtractorTest/integration1.txt";
	REQUIRE(std::filesystem::exists(testFileName));
	SimpleParserFacade parser(testFileName);
	std::shared_ptr<ASTNode> tree_ptr = parser.parse();

	std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
	std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
	FDesignExtractor fde(tree_ptr, pkbWriterManager);
	REQUIRE_NOTHROW(fde.extractAll());

	auto pkbReader = pkb->getPKBReaderManager();
	auto a = pkbReader->getParentReader()->getParent(7);
	std::unordered_set<int> expectedParent = { 6 };
	std::unordered_set<int> expectedParentT = { 2, 6 };
	REQUIRE(a == expectedParent);
	auto b = pkbReader->getParentTReader()->getParentT(7);
	REQUIRE(b == expectedParentT);

	auto c = pkbReader->getFollowsReader()->getPostFollows(2);
	std::unordered_set<int> expectedFollows = { 10 };
	REQUIRE(c == expectedFollows);
	auto d = pkbReader->getFollowsTReader()->getPostFollowsT(2);
	std::unordered_set<int> expectedFollowsT = { 10, 13 };
	REQUIRE(d == expectedFollowsT);
}