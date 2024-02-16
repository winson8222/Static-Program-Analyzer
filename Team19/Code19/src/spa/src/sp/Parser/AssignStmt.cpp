#include "AssignStmt.h"
#include <iostream>

AssignStmt::AssignStmt(const LexicalToken& variable, const LexicalToken& expr, int start, int end) {
	this->variable = variable;
	this->expr = expr;
	this->lines = std::make_pair(start, end);
}

int AssignStmt::getStartLine() const {
	return this->lines.first;
}

int AssignStmt::getEndLine() const {
	return this->lines.second;
}

std::shared_ptr<ASTNode> AssignStmt::buildTree() {
	std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
		ASTNodeType::ASSIGN, this->lines.first, Utility::getASTNodeType(ASTNodeType::ASSIGN)
	);

	std::shared_ptr<ASTNode> variable_name = std::make_shared<ASTNode>(
		ASTNodeType::VARIABLE, this->lines.second, this->variable.getValue()
	);

	std::shared_ptr<ASTNode> expression = std::make_shared<ASTNode>(
		ASTNodeType::VARIABLE, this->lines.second, this->expr.getValue()
	);

	tree.get()->addChild(variable_name);
	tree.get()->addChild(expression);

	return tree;
}