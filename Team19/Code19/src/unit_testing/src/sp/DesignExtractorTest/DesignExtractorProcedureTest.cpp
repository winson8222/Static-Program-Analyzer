#include "sp/DesignExtractor/DesignExtractor.h"
#include "sp/AST/ASTNode.h"
#include "sp/Parser/SimpleParserFacade.h"
#include "pkb/PKBManager.h"
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

    SimpleParserFacade parser(testFileName);
    std::shared_ptr<ASTNode> tree_ptr = parser.parse();

    PKBManager pkbManager;
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager.getPKBWriterManager();
    DesignExtractor designExtractor(tree_ptr, pkbWriterManager);

    std::unordered_set<std::string> actual = designExtractor.extractProcedures();
    std::unordered_set<std::string> expected = { "Procedure", "Procedure", "Procedure" };

    REQUIRE(actual == expected);
}

TEST_CASE("Test single procedure extractor", "[parseProcedure]") {
    const std::string testFileName = "../../../../../tests/sp/ParserTest/Procedure1.txt";
    REQUIRE(std::filesystem::exists(testFileName));

    SimpleParserFacade parser(testFileName);
    std::shared_ptr<ASTNode> tree_ptr = parser.parse();

    PKBManager pkbManager;
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager.getPKBWriterManager();
    DesignExtractor designExtractor(tree_ptr, pkbWriterManager);

    std::unordered_set<std::string> actual = designExtractor.extractProcedures();
    std::unordered_set<std::string> expected = { "Procedure" };

    REQUIRE(actual == expected);
}