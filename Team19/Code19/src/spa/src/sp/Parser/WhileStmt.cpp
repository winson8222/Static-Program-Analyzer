#include "WhileStmt.h"
#include <iostream>

WhileStmt::WhileStmt(const LexicalToken& variable, int start, int end) {
	this->variable = variable;
	this->lines = std::make_pair(start, end);
}

int WhileStmt::getStartLine() const {
	return this->lines.first;
}

int WhileStmt::getEndLine() const {
	return this->lines.second;
}

std::shared_ptr<ASTNode> WhileStmt::buildTree() {
	std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
		ASTNodeType::WHILE, this->lines.first, Utility::getASTNodeType(ASTNodeType::WHILE)
	);

	std::shared_ptr<ASTNode> child = std::make_shared<ASTNode>(
		ASTNodeType::VARIABLE, this->lines.second, this->variable.getValue()
	);

	tree.get()->addChild(child);

	return tree;
}