#include "catch.hpp"
#include "sp/ControlFlow/CFGNode.h"

TEST_CASE("CFGNode default constructor") {
    auto node = std::make_shared<CFGNode>();
    REQUIRE(node->getLineNumber() == -1);
    REQUIRE(node->getChildren().empty() == true);
    REQUIRE(node->isEndOfProcedure() == true);
}

TEST_CASE("CFGNode constructor with line number") {
    int line_number = 10;
    auto node = std::make_shared<CFGNode>(line_number);
    REQUIRE(node->getLineNumber() == line_number);
    REQUIRE(node->getChildren().empty() == true);
    REQUIRE(node->isEndOfProcedure() == false);
}

TEST_CASE("CFGNode end of procedure node") {
    auto node = CFGNode::getDummyNode();
    REQUIRE(node->getLineNumber() == -1);
    REQUIRE(node->getChildren().empty() == true);
    REQUIRE(node->isEndOfProcedure() == true);
}

TEST_CASE("Child addition to CFGNode", "[CFGNode]") {
    auto parent = std::make_shared<CFGNode>();
    auto child = std::make_shared<CFGNode>();
    parent->addChild(child);
    REQUIRE(parent->getChildren().size() == 1);
    REQUIRE(parent->getChildren()[0] == child);
}

TEST_CASE("While loop addition to CFGNode", "[CFGNode]") {
    auto parent = std::make_shared<CFGNode>();
    auto child = std::make_shared<CFGNode>();
    parent->addChild(child);
    child->addChild(parent);
    REQUIRE(parent->getChildren().size() == 1);
    REQUIRE(parent->getChildren()[0] == child);

    REQUIRE(child->getChildren().size() == 1);
    REQUIRE(child->getChildren()[0] == parent);
}
