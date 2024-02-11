#include "sp/ast/AST.h"
#include "sp/AST/ASTNode.h"
#include "catch.hpp"
#include <fstream>
#include <filesystem>
#include <vector>

TEST_CASE("ast test 1", "[readFileToString]") {
    ASTNode ast1 = ASTNode(ASTNodeType::ADD, 1);
    REQUIRE(ast1.type == ASTNodeType::ADD);
    REQUIRE(ast1.lineNumber == 1);

    ASTNode ast2 = ASTNode(ASTNodeType::VARIABLE, 3);
    REQUIRE(ast2.type == ASTNodeType::VARIABLE);
    REQUIRE(ast2.lineNumber == 3);

    ast2.setValue("y");
    REQUIRE(ast2.value == "y");
}


TEST_CASE("ast test 2", "[readFileToString]") {
    ASTNode ast1 = ASTNode(ASTNodeType::ADD, 1);
    std::unique_ptr<ASTNode> rootNode = std::make_unique<ASTNode>(ASTNodeType::ASSIGN, 1);
    std::unique_ptr<ASTNode> childNode1 = std::make_unique<ASTNode>(ASTNodeType::VARIABLE, 1);
    std::unique_ptr<ASTNode> childNode2 = std::make_unique<ASTNode>(ASTNodeType::CONSTANT, 1);

    AST ast(std::move(rootNode));

    // Access the root node of the AST
    const ASTNode* root = ast.getRoot();
    REQUIRE(root->lineNumber == 1);
    REQUIRE(root->type == ASTNodeType::ASSIGN);
}