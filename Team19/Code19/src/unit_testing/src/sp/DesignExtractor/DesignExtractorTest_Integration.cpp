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

TEST_CASE("temp test") {
    const std::string testFileName = "../../../../../tests/sp/DesignExtractorTest/int1.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    SimpleParserFacade parser(testFileName);
    std::shared_ptr<ASTNode> tree_ptr = parser.parse();

    std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
    DesignExtractorFacade fde(tree_ptr, pkbWriterManager);
    REQUIRE_NOTHROW(fde.extractAll());

    std::cout << tree_ptr->toString() << std::endl;

    auto reader = pkb->getPKBReaderManager();
    auto temp = reader->getModifiesSReader()->getAllVariablesModifiedByAnyStmt();
    for (auto i : temp) {
		std::cout << i << std::endl;
	}
}

TEST_CASE("Test Parser-Visitor-Extractor-PKB integration") {
    const std::string testFileName = "../../../../../tests/sp/DesignExtractorTest/Integration.txt";
    REQUIRE(std::filesystem::exists(testFileName));
    SimpleParserFacade parser(testFileName);
    std::shared_ptr<ASTNode> tree_ptr = parser.parse();

    std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
    DesignExtractorFacade fde(tree_ptr, pkbWriterManager);
    REQUIRE_NOTHROW(fde.extractAll());

    auto pkbReader = pkb->getPKBReaderManager();

    std::unordered_set<int> a = pkbReader->getParentReader()->getParent(7);
    std::unordered_set<int> expectedParent = { 6 };
    REQUIRE(a == expectedParent);

    std::unordered_set<int> expectedParentT = { 1, 4 };
    std::unordered_set<int> b = pkbReader->getParentTReader()->getParentT(5);
    REQUIRE(b == expectedParentT);

    std::unordered_set<int> c = pkbReader->getFollowsReader()->getPostFollows(6);
    std::unordered_set<int> expectedFollows = { 8 };
    REQUIRE(c == expectedFollows);

    std::unordered_set<int> d = pkbReader->getFollowsTReader()->getPostFollowsT(1);
    std::unordered_set<int> expectedFollowsT = { 6, 8 };
    REQUIRE(d == expectedFollowsT);

    std::unordered_set<std::string> e = pkbReader->getVariableReader()->getAllVariables();
    std::unordered_set<std::string> expectedVariables = { "x", "y", "z" };
    REQUIRE(e == expectedVariables);

    std::unordered_set<int> f = pkbReader->getConstantReader()->getAllConstants();
    std::unordered_set<int> expectedConstants = {0, 1};
    REQUIRE(f == expectedConstants);

    std::unordered_set<std::string> g = pkbReader->getProcedureReader()->getAllProcedures();
    std::unordered_set<std::string> expectedProcedures = { "proc1", "p"};
    REQUIRE(g == expectedProcedures);

    std::unordered_set<int> h = pkbReader->getStatementReader()->getAllStatements();
    std::unordered_set<int> expectedStatements = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    REQUIRE(h == expectedStatements);

    std::unordered_set<int> i = pkbReader->getPrintReader()->getAllPrints();
    std::unordered_set<int> expectedPrints = { 2 };
    REQUIRE(i == expectedPrints);

    std::unordered_set<int> j = pkbReader->getReadReader()->getAllReads();
    std::unordered_set<int> expectedReads = { 3 };
    REQUIRE(j == expectedReads);

    std::unordered_set<int> k = pkbReader->getCallReader()->getAllCalls();
    std::unordered_set<int> expectedCalls = { 8 };
    REQUIRE(k == expectedCalls);

    std::unordered_set<int> l = pkbReader->getWhileReader()->getAllWhiles();
    std::unordered_set<int> expectedWhiles = { 4, 6 };
    REQUIRE(l == expectedWhiles);

    std::unordered_set<int> m = pkbReader->getIfReader()->getAllIfs();
    std::unordered_set<int> expectedIfs = { 1 };
    REQUIRE(m == expectedIfs);

    std::unordered_set<int> n = pkbReader->getAssignReader()->getAllAssigns();
    std::unordered_set<int> expectedAssigns = { 5, 7, 9 };
    REQUIRE(n == expectedAssigns);
}