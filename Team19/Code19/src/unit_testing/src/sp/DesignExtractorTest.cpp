#include "sp/DesignExtractor/DesignExtractor.h"
#include "sp/AST/ASTNode.h"
#include "pkb/PKBManager.h"
#include "pkb/PKBWriter.h"
#include "sp/Utility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <vector>

TEST_CASE("Basic system tests for DesignExtractor", "[DesignExtractor::extract]") {
    const std::string testFileName = "../../../../../tests/sp/TokenizerTest/sourcefile1.txt";
    REQUIRE(std::filesystem::exists(testFileName));

    PKBManager pkbManager;
    std::shared_ptr<PKBWriter> pkbWriter = pkbManager.getPKBWriter();

    DesignExtractor designExtractor(std::make_shared<ASTNode>(), pkbWriter);
    std::cout << "First stage now\n\n" << std::endl;

    auto value1 = designExtractor.pkbWriter;
    auto ast1 = designExtractor.root;

    auto ast2 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "i");
    auto ast3 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 1, Utility::getASTNodeType(ASTNodeType::ASSIGN));
    auto ast4 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1");

    auto ast5 = std::make_shared<ASTNode>(ASTNodeType::WHILE, 2, Utility::getASTNodeType(ASTNodeType::WHILE));
    auto ast6 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 2, "i");
    auto ast7 = std::make_shared<ASTNode>(ASTNodeType::LESSER, 2, Utility::getASTNodeType(ASTNodeType::LESSER));
    auto ast8 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 2, "3");

    auto ast9 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "i");
    auto ast10 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 3, Utility::getASTNodeType(ASTNodeType::ASSIGN));
    auto ast11 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "j");
    auto ast12 = std::make_shared<ASTNode>(ASTNodeType::ADD, 3, Utility::getASTNodeType(ASTNodeType::ADD));
    auto ast13 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 3, "1");

    ast12->addChild(std::move(ast11));
    ast12->addChild(std::move(ast13));
    ast10->addChild(std::move(ast9));
    ast10->addChild(std::move(ast12));

    ast7->addChild(std::move(ast6));
    ast7->addChild(std::move(ast8));
    ast5->addChild(std::move(ast7));
    ast5->addChild(std::move(ast10));

    ast3->addChild(std::move(ast2));
    ast3->addChild(std::move(ast4));

    ast1->addChild(std::move(ast3));
    ast1->addChild(std::move(ast5));

    auto value2 = designExtractor.extractVariables();

    std::cout << "Extracted variables:" << std::endl; 
    for (auto& var : value2) {
		std::cout << var << std::endl;
	}
    std::cout << "end\n" << std::endl;

    auto value3 = designExtractor.extractConstants();

    std::cout << "Extracted constants:" << std::endl;
    for (auto& var : value3) {
        std::cout << var << std::endl;
    }
    std::cout << "end\n" << std::endl;
}
