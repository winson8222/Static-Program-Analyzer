#include "catch.hpp"

#include <iostream>
#include <unordered_set>
#include <vector>
#include <sstream>

#include "sp/ast/ASTNode.h"
#include "sp/AST/ASTUtility.h"


TEST_CASE("sp/ast/ASTNode") {
    SECTION("Check Type") {
        ASTNode astAdd = ASTNode(ASTNodeType::ADD, 1, ASTUtility::getASTNodeType(ASTNodeType::ADD));
        ASTNode astSubtract = ASTNode(ASTNodeType::SUBTRACT, 1, ASTUtility::getASTNodeType(ASTNodeType::SUBTRACT));
        ASTNode astMultiply = ASTNode(ASTNodeType::MULTIPLY, 1, ASTUtility::getASTNodeType(ASTNodeType::MULTIPLY));
        ASTNode astDivide = ASTNode(ASTNodeType::DIVIDE, 1, ASTUtility::getASTNodeType(ASTNodeType::DIVIDE));
        ASTNode astModulo = ASTNode(ASTNodeType::MODULO, 1, ASTUtility::getASTNodeType(ASTNodeType::MODULO));
        ASTNode astVariable = ASTNode(ASTNodeType::VARIABLE, 3, "x");

        SECTION("ASTNodeType::Add") {
            REQUIRE(astAdd.type == ASTNodeType::ADD);
            REQUIRE(astAdd.lineNumber == 1);
        }

        SECTION("ASTNodeType::Subtract") {
            REQUIRE(astSubtract.type == ASTNodeType::SUBTRACT);
            REQUIRE(astSubtract.lineNumber == 1);
        }

        SECTION("ASTNodeType::Multiply") {
            REQUIRE(astMultiply.type == ASTNodeType::MULTIPLY);
            REQUIRE(astMultiply.lineNumber == 1);
        }

        SECTION("ASTNodeType::Divide") {
            REQUIRE(astDivide.type == ASTNodeType::DIVIDE);
            REQUIRE(astDivide.lineNumber == 1);
        }

        SECTION("ASTNodeType::Modulo") {
            REQUIRE(astModulo.type == ASTNodeType::MODULO);
            REQUIRE(astModulo.lineNumber == 1);
        }

        SECTION("ASTNodeType::Variable") {
            REQUIRE(astVariable.type == ASTNodeType::VARIABLE);
            REQUIRE(astVariable.lineNumber == 3);
            REQUIRE(astVariable.value == "x");
            SECTION("setValue") {
                astVariable.setValue("y");
                REQUIRE(astVariable.value == "y");
            }
            SECTION("addChild") {
                auto ast2_ptr = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "x");
                auto ast3_ptr = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1");
                astVariable.addChild(std::move(ast2_ptr));
                astVariable.addChild(std::move(ast3_ptr));
                REQUIRE(astVariable.children.size() == 2);
                REQUIRE(astVariable.children[0]->type == ASTNodeType::VARIABLE);
                REQUIRE(astVariable.children[0]->value == "x");
                REQUIRE(astVariable.children[0]->lineNumber == 1);
                REQUIRE(astVariable.children[1]->type == ASTNodeType::CONSTANT);
                REQUIRE(astVariable.children[1]->value == "1");
                REQUIRE(astVariable.children[1]->lineNumber == 1);
            }
        }
    }

    SECTION("hash") {
        auto ast1 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, ASTUtility::getASTNodeType(ASTNodeType::ADD));
        auto ast2 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, ASTUtility::getASTNodeType(ASTNodeType::ADD));
        REQUIRE(ast1->hash() == ast2->hash());
    }

    SECTION("toString") {
        /*
        i = 1;
        while (i < 3) {
            i = i + 1;
        }
        */
        // Initialize the ASTs
        ASTNode ast1 = ASTNode(ASTNodeType::STATEMENT_LIST, 1, ASTUtility::getASTNodeType(ASTNodeType::STATEMENT_LIST));

        auto ast2 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "i");
        auto ast3 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 1, ASTUtility::getASTNodeType(ASTNodeType::ASSIGN));
        auto ast4 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1");

        auto ast5 = std::make_shared<ASTNode>(ASTNodeType::WHILE, 2, ASTUtility::getASTNodeType(ASTNodeType::WHILE));
        auto ast6 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 2, "i");
        auto ast7 = std::make_shared<ASTNode>(ASTNodeType::LESSER, 2, ASTUtility::getASTNodeType(ASTNodeType::LESSER));
        auto ast8 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 2, "3");

        auto ast9 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "i");
        auto ast10 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 3, ASTUtility::getASTNodeType(ASTNodeType::ASSIGN));
        auto ast11 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "i");
        auto ast12 = std::make_shared<ASTNode>(ASTNodeType::ADD, 3, ASTUtility::getASTNodeType(ASTNodeType::ADD));
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
        REQUIRE(lines.size() == 14);
        REQUIRE(lines.find("        Type: Constant, Line Number: 3, Value: 1") != lines.end());
    }

    SECTION("getRPNForm") {
        std::shared_ptr<ASTNode> ast1 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, ASTUtility::getASTNodeType(ASTNodeType::ADD));
        ast1->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "x"));
        ast1->addChild(std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1"));

        REQUIRE(ast1->getRPNForm() == "x1+");

        std::shared_ptr<ASTNode> ast2 = std::make_shared<ASTNode>(ASTNodeType::MULTIPLY, 1, ASTUtility::getASTNodeType(ASTNodeType::MULTIPLY));
        ast2->addChild(ast1);
        ast2->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "y"));

        REQUIRE(ast2->getRPNForm() == "x1+y*");

        std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, ASTUtility::getASTNodeType(ASTNodeType::ADD));
        ast3->addChild(ast2);
        ast3->addChild(std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "2"));

        REQUIRE(ast3->getRPNForm() == "x1+y*2+");
    }
}

