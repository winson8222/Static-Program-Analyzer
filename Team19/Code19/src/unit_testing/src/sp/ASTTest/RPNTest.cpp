#include "sp/ast/AST.h"
#include "sp/AST/ASTNode.h"
#include "sp/Utility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <vector>

TEST_CASE("rpn test 1", "[readFileToString]") {
    std::shared_ptr<ASTNode> ast1 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, Utility::getASTNodeType(ASTNodeType::ADD));
    ast1->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "x"));
    ast1->addChild(std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1"));

    REQUIRE(ast1->getRPNForm() == "x1+");

    std::shared_ptr<ASTNode> ast2 = std::make_shared<ASTNode>(ASTNodeType::MULTIPLY, 1, Utility::getASTNodeType(ASTNodeType::MULTIPLY));
    ast2->addChild(ast1);
    ast2->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "y"));

    REQUIRE(ast2->getRPNForm() == "x1+y*");

    std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, Utility::getASTNodeType(ASTNodeType::ADD));
    ast3->addChild(ast2);
    ast3->addChild(std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "2"));

    REQUIRE(ast3->getRPNForm() == "x1+y*2+");
}