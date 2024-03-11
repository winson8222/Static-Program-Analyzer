#include "catch.hpp"

#include <iostream>
#include <unordered_set>
#include <vector>
#include <sstream>

#include "sp/AST/ASTNode.h"
#include "sp/AST/ASTUtility.h"


TEST_CASE("sp/ast/ASTNode") {
    SECTION("Check Type") {
        ASTNode astAdd = ASTNode(ASTNodeType::ADD, 1, ASTUtility::getASTNodeType.find(ASTNodeType::ADD)->second);
        ASTNode astSubtract = ASTNode(ASTNodeType::SUBTRACT, 1, ASTUtility::getASTNodeType.find(ASTNodeType::SUBTRACT)->second);
        ASTNode astMultiply = ASTNode(ASTNodeType::MULTIPLY, 1, ASTUtility::getASTNodeType.find(ASTNodeType::MULTIPLY)->second);
        ASTNode astDivide = ASTNode(ASTNodeType::DIVIDE, 1, ASTUtility::getASTNodeType.find(ASTNodeType::DIVIDE)->second);
        ASTNode astModulo = ASTNode(ASTNodeType::MODULO, 1, ASTUtility::getASTNodeType.find(ASTNodeType::MODULO)->second);
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
        auto ast1 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, ASTUtility::getASTNodeType.find(ASTNodeType::ADD)->second);
        auto ast2 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, ASTUtility::getASTNodeType.find(ASTNodeType::ADD)->second);
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
        ASTNode ast1 = ASTNode(ASTNodeType::STATEMENT_LIST, 1, ASTUtility::getASTNodeType.find(ASTNodeType::STATEMENT_LIST)->second);

        auto ast2 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "i");
        auto ast3 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 1, ASTUtility::getASTNodeType.find(ASTNodeType::ASSIGN)->second);
        auto ast4 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1");

        auto ast5 = std::make_shared<ASTNode>(ASTNodeType::WHILE, 2, ASTUtility::getASTNodeType.find(ASTNodeType::WHILE)->second);
        auto ast6 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 2, "i");
        auto ast7 = std::make_shared<ASTNode>(ASTNodeType::LESSER, 2, ASTUtility::getASTNodeType.find(ASTNodeType::LESSER)->second);
        auto ast8 = std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 2, "3");

        auto ast9 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "i");
        auto ast10 = std::make_shared<ASTNode>(ASTNodeType::ASSIGN, 3, ASTUtility::getASTNodeType.find(ASTNodeType::ASSIGN)->second);
        auto ast11 = std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 3, "i");
        auto ast12 = std::make_shared<ASTNode>(ASTNodeType::ADD, 3, ASTUtility::getASTNodeType.find(ASTNodeType::ADD)->second);
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
        // representing x + 1
        std::shared_ptr<ASTNode> ast1 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, ASTUtility::getASTNodeType.find(ASTNodeType::ADD)->second);
        ast1->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "x"));
        ast1->addChild(std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "1"));

        REQUIRE(ast1->getRPNForm() == "'x''1''+'");

        // representing (x + 1) * y
        std::shared_ptr<ASTNode> ast2 = std::make_shared<ASTNode>(ASTNodeType::MULTIPLY, 1, ASTUtility::getASTNodeType.find(ASTNodeType::MULTIPLY)->second);
        ast2->addChild(ast1);
        ast2->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "y"));

        REQUIRE(ast2->getRPNForm() == "'x''1''+''y''*'");

        // representing (x + 1) * y + 2
        std::shared_ptr<ASTNode> ast3 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, ASTUtility::getASTNodeType.find(ASTNodeType::ADD)->second);
        ast3->addChild(ast2);
        ast3->addChild(std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "2"));

        REQUIRE(ast3->getRPNForm() == "'x''1''+''y''*''2''+'");

        // representing (x + 1) * (y / 2)
        std::shared_ptr<ASTNode> ast4 = std::make_shared<ASTNode>(ASTNodeType::MULTIPLY, 1, ASTUtility::getASTNodeType.find(ASTNodeType::MULTIPLY)->second);
        ast4->addChild(ast1);
        std::shared_ptr<ASTNode> ast5 = std::make_shared<ASTNode>(ASTNodeType::DIVIDE, 1, ASTUtility::getASTNodeType.find(ASTNodeType::DIVIDE)->second);
        ast5->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "y"));
        ast5->addChild(std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "2"));
        ast4->addChild(ast5);

        REQUIRE(ast4->getRPNForm() == "'x''1''+''y''2''/''*'");

        // representing (x + 1) * ((y - 6) * 2)
        std::shared_ptr<ASTNode> ast6 = std::make_shared<ASTNode>(ASTNodeType::MULTIPLY, 1, ASTUtility::getASTNodeType.find(ASTNodeType::MULTIPLY)->second);
        ast6->addChild(ast1);
        std::shared_ptr<ASTNode> ast7 = std::make_shared<ASTNode>(ASTNodeType::MULTIPLY, 1, ASTUtility::getASTNodeType.find(ASTNodeType::MULTIPLY)->second);
        std::shared_ptr<ASTNode> ast8 = std::make_shared<ASTNode>(ASTNodeType::SUBTRACT, 1, ASTUtility::getASTNodeType.find(ASTNodeType::SUBTRACT)->second);
        ast8->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "y"));
        ast8->addChild(std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "6"));
        ast7->addChild(ast8);
        ast7->addChild(std::make_shared<ASTNode>(ASTNodeType::CONSTANT, 1, "2"));
        ast6->addChild(ast7);

        REQUIRE(ast6->getRPNForm() == "'x''1''+''y''6''-''2''*''*'");

        // representing (a + b) * ((c / d) - (e * f))
        std::shared_ptr<ASTNode> ast9 = std::make_shared<ASTNode>(ASTNodeType::MULTIPLY, 1, ASTUtility::getASTNodeType.find(ASTNodeType::MULTIPLY)->second);
        std::shared_ptr<ASTNode> ast10 = std::make_shared<ASTNode>(ASTNodeType::ADD, 1, ASTUtility::getASTNodeType.find(ASTNodeType::ADD)->second);
        ast10->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "a"));
        ast10->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "b"));
        ast9->addChild(ast10);
        std::shared_ptr<ASTNode> ast11 = std::make_shared<ASTNode>(ASTNodeType::SUBTRACT, 1, ASTUtility::getASTNodeType.find(ASTNodeType::SUBTRACT)->second);
        std::shared_ptr<ASTNode> ast12 = std::make_shared<ASTNode>(ASTNodeType::DIVIDE, 1, ASTUtility::getASTNodeType.find(ASTNodeType::DIVIDE)->second);
        ast12->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "c"));
        ast12->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "d"));
        ast11->addChild(ast12);
        std::shared_ptr<ASTNode> ast13 = std::make_shared<ASTNode>(ASTNodeType::MULTIPLY, 1, ASTUtility::getASTNodeType.find(ASTNodeType::MULTIPLY)->second);
        ast13->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "e"));
        ast13->addChild(std::make_shared<ASTNode>(ASTNodeType::VARIABLE, 1, "f"));
        ast11->addChild(ast13);
        ast9->addChild(ast11);

        REQUIRE(ast9->getRPNForm() == "'a''b''+''c''d''/''e''f''*''-''*'");
    }
}

