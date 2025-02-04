#include "StmtList.h"
#include <iostream>

StmtList::StmtList(int start, int end, std::vector<std::shared_ptr<ASTNode>> statements) {
	this->lines = std::make_pair(start, end);
	this->statements = statements;
}

int StmtList::getStartLine() const {
	return this->lines.first;
}

int StmtList::getEndLine() const {
	return this->lines.second;
}

std::shared_ptr<ASTNode> StmtList::buildTree() {
	std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
		ASTNodeType::STATEMENT_LIST, this->lines.first, Utility::getASTNodeType(ASTNodeType::STATEMENT_LIST)
	);

	for (auto child : this->statements) {
		tree.get()->addChild(child);
	}

	return tree;
}