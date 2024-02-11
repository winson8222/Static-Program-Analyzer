#include "sp/ast/AST.h"
#include "sp/AST/ASTNode.h"
#include "sp/AST/Utility.h"
#include "catch.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <unordered_set>
#include <vector>

TEST_CASE("ast test 1", "[readFileToString]") {
    ASTNode ast1 = ASTNode(ASTNodeType::ADD, 1, Utility::getASTNodeType(ASTNodeType::ADD));
    REQUIRE(ast1.type == ASTNodeType::ADD);
    REQUIRE(ast1.lineNumber == 1);

    ASTNode ast2 = ASTNode(ASTNodeType::VARIABLE, 3, "x");
    REQUIRE(ast2.type == ASTNodeType::VARIABLE);
    REQUIRE(ast2.lineNumber == 3);
    REQUIRE(ast2.value == "x");

    ast2.setValue("y");
    REQUIRE(ast2.value == "y");

    auto ast2_ptr = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "x");
    auto ast3_ptr = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1");

    auto ast4_ptr = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 2, "2");
    ast3_ptr->addChild(std::move(ast4_ptr));
    ast1.addChild(std::move(ast2_ptr));
    ast1.addChild(std::move(ast3_ptr));
}


TEST_CASE("ast test 2", "[readFileToString]") {
    ASTNode ast1 = ASTNode(ASTNodeType::ADD, 1, Utility::getASTNodeType(ASTNodeType::ADD));
    auto rootNode = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 1, Utility::getASTNodeType(ASTNodeType::ASSIGN));
    auto childNode1 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "x");
    auto childNode2 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1");

    AST ast(std::move(rootNode));

    // Access the root node of the AST
    const ASTNode* root = ast.getRoot();
    REQUIRE(root->lineNumber == 1);
    REQUIRE(root->type == ASTNodeType::ASSIGN);
}

// build a tree with the while statement?
TEST_CASE("ast test 3", "[readFileToString]") {
    /*
    i = 1;
    while (i < 3) {
        i = i + 1;
    }
    */
    ASTNode ast1 = ASTNode(ASTNodeType::STATEMENT_LIST, 1, Utility::getASTNodeType(ASTNodeType::STATEMENT_LIST));

    auto ast2 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "i");
    auto ast3 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 1, Utility::getASTNodeType(ASTNodeType::ASSIGN));
    auto ast4 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1");

    auto ast5 = std::make_shared<ASTNode>(ASTNodeType::WHILE, 2, Utility::getASTNodeType(ASTNodeType::WHILE));
    auto ast6 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 2, "i");
    auto ast7 = std::make_shared<ASTNode>(ASTNodeType::LESSER, 2, Utility::getASTNodeType(ASTNodeType::LESSER));
    auto ast8 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 2, "3");

    auto ast9 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "i");
    auto ast10 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 3, Utility::getASTNodeType(ASTNodeType::ASSIGN));
    auto ast11 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "i");
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

    ast1.addChild(std::move(ast3));
    ast1.addChild(std::move(ast5));
    
    std::string output;
    REQUIRE_NOTHROW(output = ast1.toString());

    std::stringstream ss(output);

    // Vector to store the split strings
    std::unordered_set<std::string> lines;

    // Temporary string to store each line
    std::string line;

    // Read each line using std::getline and push it into the vector
    while (std::getline(ss, line, '\n')) {
        lines.insert(line);
    }
    std::cout << output << std::endl;
    REQUIRE(lines.size() == 14);
    REQUIRE(lines.find("        Type: Constant, Line Number: 3, Value: 1") != lines.end());
}

TEST_CASE("ast test 4", "[readFileToString]") {
    auto ast1 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, Utility::getASTNodeType(ASTNodeType::ADD));
    auto ast2 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, Utility::getASTNodeType(ASTNodeType::ADD));
    std::cout << ast1->hash() << std::endl;

}