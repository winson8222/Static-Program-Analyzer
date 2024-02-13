#include "sp/DesignExtractor/DesignExtractor.h"
#include "sp/AST/ASTNode.h"
#include "sp/Parser/SimpleParser.h"
#include "pkb/PKBManager.h"
#include "pkb/PKBWriter.h"
#include "sp/Utility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

TEST_CASE("Test multiple procedure extractor", "[parseProcedure]") {
    // Generate test file
    const std::string testFileName = "../../../../../tests/sp/ParserTest/Program1.txt";
    REQUIRE(std::filesystem::exists(testFileName));

    SimpleParser parser(testFileName);
    std::shared_ptr<ASTNode> tree_ptr = parser.parseProgram();

    PKBManager pkbManager;
    std::shared_ptr<PKBWriter> pkbWriter = pkbManager.getPKBWriter();
    DesignExtractor designExtractor(tree_ptr, pkbWriter);

    std::unordered_set<std::string> actual = designExtractor.extractProcedures();
    std::unordered_set<std::string> expected = { "Procedure", "Procedure", "Procedure" };

    REQUIRE(actual == expected);
}

TEST_CASE("Test single procedure extractor", "[parseProcedure]") {
    const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure1.txt";
    REQUIRE(std::filesystem::exists(testFileName));

    SimpleParser parser(testFileName);
    std::shared_ptr<ASTNode> tree_ptr = parser.parseProgram();

    PKBManager pkbManager;
    std::shared_ptr<PKBWriter> pkbWriter = pkbManager.getPKBWriter();
    DesignExtractor designExtractor(tree_ptr, pkbWriter);

    std::unordered_set<std::string> actual = designExtractor.extractProcedures();
    std::unordered_set<std::string> expected = { "Procedure" };

    REQUIRE(actual == expected);
}