#include "sp/DesignExtractor/DesignExtractor.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"
#include "sp/Utility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <vector>


TEST_CASE(" tests for Entity Extractor", "[DesignExtractor::extract]") {
    PKBManager pkbManager;
    std::shared_ptr<PKBWriterManager> pkbWriterManager = pkbManager.getPKBWriterManager();

    DesignExtractor designExtractor(std::make_shared<ASTNode>(), pkbWriterManager);

    auto value1 = designExtractor.pkbWriterManager;
    auto ast1 = designExtractor.root;

    // Create AST nodes with different names and values
    auto ast2_i = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "i");
    auto ast3_i = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 1, Utility::getASTNodeType(ASTNodeType::ASSIGN));
    auto ast4_1 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1");

    auto ast2_k = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "k");
    auto ast3_k = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 1, Utility::getASTNodeType(ASTNodeType::ASSIGN));
    auto ast4_3 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "3");

    auto ast5_while = std::make_shared<ASTNode>(ASTNodeType::WHILE, 2, Utility::getASTNodeType(ASTNodeType::WHILE));
    auto ast6_k = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 2, "k");
    auto ast7_lesser = std::make_shared<ASTNode>(ASTNodeType::LESSER, 2, Utility::getASTNodeType(ASTNodeType::LESSER));
    auto ast8_3 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 2, "5");

    auto ast9_i = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "i");
    auto ast10_assign = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 3, Utility::getASTNodeType(ASTNodeType::ASSIGN));
    auto ast11_j = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "j");
    auto ast12_add = std::make_shared<ASTNode>(ASTNodeType::ADD, 3, Utility::getASTNodeType(ASTNodeType::ADD));
    auto ast13_1 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 3, "1");

    ast12_add->addChild(std::move(ast11_j));
    ast12_add->addChild(std::move(ast13_1));
    ast10_assign->addChild(std::move(ast9_i));
    ast10_assign->addChild(std::move(ast12_add));

    ast7_lesser->addChild(std::move(ast6_k));
    ast7_lesser->addChild(std::move(ast8_3));
    ast5_while->addChild(std::move(ast7_lesser));
    ast5_while->addChild(std::move(ast10_assign));

    ast3_i->addChild(std::move(ast2_i));
    ast3_i->addChild(std::move(ast4_1));

    ast3_k->addChild(std::move(ast2_k));
    ast3_k->addChild(std::move(ast4_3));

    ast1->addChild(std::move(ast3_i));
    ast1->addChild(std::move(ast3_k));
    ast1->addChild(std::move(ast5_while));

    // Extract variables and constants
    std::unordered_set<std::string> extractedVariables = designExtractor.extractVariables();
    std::unordered_set<std::string> extractedConstants = designExtractor.extractConstants();

    std::unordered_set<std::string> expectedVariables = { "i", "j", "k" };
    std::unordered_set<std::string> expectedConstants = { "1", "3", "5" };

    REQUIRE(extractedVariables == expectedVariables);
    REQUIRE(extractedConstants == expectedConstants);
}
