#include "Procedure.h"
#include <iostream>

Procedure::Procedure(int start, int end, std::shared_ptr<ASTNode> statementListTree) {
	this->lines = std::make_pair(start, end);
	this->statementListTree = statementListTree;
}

int Procedure::getStartLine() const {
	return this->lines.first;
}

int Procedure::getEndLine() const {
	return this->lines.second;
}

std::shared_ptr<ASTNode> Procedure::buildTree() {
	std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
		ASTNodeType::PROCEDURE, this->lines.first, Utility::getASTNodeType(ASTNodeType::PROCEDURE)
	);

	tree.get()->addChild(this->statementListTree);

	return tree;
}