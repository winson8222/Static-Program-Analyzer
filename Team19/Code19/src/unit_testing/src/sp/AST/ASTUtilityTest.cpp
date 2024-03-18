#include "catch.hpp"

#include <iostream>
#include <unordered_set>
#include <vector>
#include <sstream>

#include "sp/AST/ASTNode.h"
#include "sp/AST/ASTUtility.h"

TEST_CASE("sp/ast/ASTNodeType") {
	SECTION("") {
		REQUIRE(ASTUtility::getASTNodeType.find(ASTNodeType::ADD)->second == "+");
		REQUIRE(ASTUtility::getASTNodeType.find(ASTNodeType::SUBTRACT)->second == "-");
		REQUIRE(ASTUtility::getASTNodeType.find(ASTNodeType::ASSIGN)->second == "assign");
		REQUIRE(ASTUtility::getASTNodeType.find(ASTNodeType::VARIABLE)->second == "Variable");
	}

	SECTION("Check if a node is statement") {
		REQUIRE(ASTUtility::nodeIsStatement(ASTNodeType::ASSIGN));
		REQUIRE(!ASTUtility::nodeIsStatement(ASTNodeType::VARIABLE));
	}

	SECTION("Check if a node is expression") {
		REQUIRE(ASTUtility::nodeIsRelExpression(ASTNodeType::GREATER_OR_EQUAL));
		REQUIRE(!ASTUtility::nodeIsRelExpression(ASTNodeType::VARIABLE));
	}

	SECTION("Check if a node is conditional expression") {
		REQUIRE(ASTUtility::nodeIsCondExpression(ASTNodeType::AND));
		REQUIRE(!ASTUtility::nodeIsCondExpression(ASTNodeType::VARIABLE));
	}

	SECTION("Check if a node is valid operator expression") {
		REQUIRE(ASTUtility::nodeIsValidOperator(ASTNodeType::ADD));
		REQUIRE(!ASTUtility::nodeIsValidOperator(ASTNodeType::VARIABLE));
	}

	SECTION("Check if a node is valid relational operator") {
		REQUIRE(!ASTUtility::nodeIsValidRelFactor(ASTNodeType::GREATER_OR_EQUAL));
		REQUIRE(ASTUtility::nodeIsValidRelFactor(ASTNodeType::VARIABLE));
	}

	SECTION("Check if a node can use") {
		REQUIRE(!ASTUtility::nodeStatementCanUses(ASTNodeType::READ));
		REQUIRE(ASTUtility::nodeStatementCanUses(ASTNodeType::ASSIGN));
		REQUIRE(ASTUtility::nodeStatementCanUses(ASTNodeType::WHILE));
	}

	SECTION("Check if a node can modify") {
		REQUIRE(ASTUtility::nodeStatementCanModifies(ASTNodeType::READ));
		REQUIRE(ASTUtility::nodeStatementCanModifies(ASTNodeType::ASSIGN));
		REQUIRE(!ASTUtility::nodeStatementCanModifies(ASTNodeType::PRINT));
	}

	SECTION("Check if a node can form valid expression") {
		REQUIRE(ASTUtility::nodeCanFormValidExpression(ASTNodeType::ADD));
		REQUIRE(ASTUtility::nodeCanFormValidExpression(ASTNodeType::LESSER));
		REQUIRE(ASTUtility::nodeCanFormValidExpression(ASTNodeType::VARIABLE));
		REQUIRE(ASTUtility::nodeCanFormValidExpression(ASTNodeType::OR));
		REQUIRE(!ASTUtility::nodeCanFormValidExpression(ASTNodeType::PROCEDURE));
		REQUIRE(!ASTUtility::nodeCanFormValidExpression(ASTNodeType::IF_ELSE_THEN));
	}

	SECTION("Check equality") {
		REQUIRE(ASTUtility::nodeIsTarget(ASTNodeType::ADD, ASTNodeType::ADD));
		REQUIRE(!ASTUtility::nodeIsTarget(ASTNodeType::ADD, ASTNodeType::SUBTRACT));
	}
}