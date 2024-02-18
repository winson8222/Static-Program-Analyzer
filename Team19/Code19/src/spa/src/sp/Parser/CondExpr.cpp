#include "CondExpr.h"
#include <iostream>

CondExpr::CondExpr(int start, int end) {
	this->lines = std::make_pair(start, end);
}

int CondExpr::getStartLine() const {
	return this->lines.first;
}

int CondExpr::getEndLine() const {
	return this->lines.second;
}

std::shared_ptr<ASTNode> CondExpr::buildTree() {
	std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
		ASTNodeType::PROCEDURE, this->lines.first, Utility::getASTNodeType(ASTNodeType::PROCEDURE)
	);

	// tree.get()->addChild(this->statementListTree);

	return tree;
}