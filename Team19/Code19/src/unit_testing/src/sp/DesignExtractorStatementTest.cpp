#include "sp/DesignExtractor/DesignExtractor.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"
#include "pkb/PKBWriter.h"
#include "sp/Utility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <vector>


TEST_CASE("Unit tests for Statement Extractor", "[DesignExtractor::extract]") {
    std::cout << "DESIGN EXTRACTOR STATEMENT TESTS\n\n" << std::endl;

    PKBManager pkbManager;
    std::shared_ptr<PKBWriter> pkbWriter = pkbManager.getPKBWriter();

    DesignExtractor designExtractor(std::make_shared<ASTNode>(), pkbWriter);

    auto value1 = designExtractor.pkbWriter;
    auto ast1 = designExtractor.root;

    // Create AST nodes with different names and values
    auto call_1 = std::make_shared<ASTNode>(ASTNodeType::CALL, 1, "call");
    auto print_2 = std::make_shared<ASTNode>(ASTNodeType::PRINT, 2, "print");
    auto call_2 = std::make_shared<ASTNode>(ASTNodeType::CALL, 3, "call");
    auto read_1 = std::make_shared<ASTNode>(ASTNodeType::READ, 4, "read");
    auto print_1 = std::make_shared<ASTNode>(ASTNodeType::PRINT, 5, "print");
    auto read_2 = std::make_shared<ASTNode>(ASTNodeType::READ, 6, "read");

    auto variable_1 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "i");
    auto variable_2 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 2, "j");
    auto variable_3 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "k");
    auto variable_4 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 4, "k");
    auto variable_5 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 5, "j");
    auto variable_6 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 6, "i");

    call_1->addChild(std::move(variable_1));
    call_2->addChild(std::move(variable_2));
    print_1->addChild(std::move(variable_3));
    print_2->addChild(std::move(variable_4));
    read_1->addChild(std::move(variable_5));
    read_2->addChild(std::move(variable_6));

    ast1->addChild(std::move(call_1));
    ast1->addChild(std::move(call_2));
    ast1->addChild(std::move(print_1));
    ast1->addChild(std::move(print_2));
    ast1->addChild(std::move(read_1));
    ast1->addChild(std::move(read_2));

    // Extract variables and constants
    std::unordered_set<int> extractedCall = designExtractor.extractCall();
    std::unordered_set<int> extractedPrint = designExtractor.extractPrint();
    std::unordered_set<int> extractedRead = designExtractor.extractRead();

    std::unordered_set<int> expectedCall = { 1, 3 };
    std::unordered_set<int> expectedPrint = { 2, 5 };
    std::unordered_set<int> expectedRead = { 4, 6 };

    REQUIRE(extractedCall == expectedCall);
    REQUIRE(extractedPrint == expectedPrint);
    REQUIRE(extractedRead == expectedRead);

    ast1->addChild(std::move(std::make_shared<ASTNode>(ASTNodeType::PROCEDURE, 7, "procedure")));
    designExtractor.extractAll();
    std::unordered_set<int> extractedStatements = designExtractor.extractStatements();
    std::unordered_set<int> expectedStatements = {1, 2, 3, 4, 5, 6};

    REQUIRE(extractedStatements == expectedStatements);
}
