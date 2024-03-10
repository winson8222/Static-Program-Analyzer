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

TEST_CASE("Test integrating PKB to SP") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure procedure {"
                                "    print print;"
                                "    read read;"
                                "    read = 5;"
                                "    print = read;"
                                "    add = read * print;"
                                "    minus = print - read;"
                                "    procedure = read + print / read;"
                                "   "
                                "    while (read < 10) {"
                                "       if (!(print > 0)) then {"
                                "          print print;"
                                "       } else {"
                                "          print read;"
                                "          procedure = add % minus;  "
                                "          if (procedure < 0) then {"
                                "              while = print + read;"
                                "              print while;"
                                "           } else {"
                                "  print procedure;"
                                "   }"
                                "      }"
                                "      }"
                                "    while (print != read) {"
                                "        procedure = procedure -1;"
                                "        print = print + 1;"
                                "    }"
                                "    if = add + minus / procedure * read - print;"
                                "    print if;"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    SimpleParserFacade parser(filename);
    std::shared_ptr<ASTNode> tree_ptr = parser.parse();

    std::shared_ptr<PKBManager> pkb = std::make_shared<PKBManager>();
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkb->getPKBWriterManager();
    DesignExtractorFacade fde(tree_ptr, pkbWriterManager);
    REQUIRE_NOTHROW(fde.extractAll());
    std::filesystem::remove(filename);
}

TEST_CASE("Test Parser-Visitor-Extractor-PKB integration") {
    std::string filename = "sample.txt";
    std::string sampleProgram = "procedure proc1 {"
                                "if (z < 0) then {"
                                "print x;"
                                "} else {"
                                "read y;"
                                "while (x < y) {"
                                "z = z + 1;"
                                "}"
                                "}"
                                "while (x < y) {"
                                "z = z + 1;"
                                "}"
                                "call p;"
                                "}"
                                ""
                                "procedure p{"
                                "x = y + z;"
                                "}";
    std::ofstream file;
    file.open(filename);
    file << sampleProgram;
    file.close();
    REQUIRE(std::filesystem::exists(filename));
    SimpleParserFacade parser(filename);
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
    std::filesystem::remove(filename);
}