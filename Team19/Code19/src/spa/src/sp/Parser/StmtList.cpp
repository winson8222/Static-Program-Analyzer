#include "StmtList.h"
#include <iostream>

StmtList::StmtList(int start, int end) {
	this->lines = std::make_pair(start, end);
}

void StmtList::addStmt(std::shared_ptr<ASTNode> statementNode) {
	this->statements.push_back(statementNode);
}

int StmtList::getStartLine() const {
	return lines.first;
}

int StmtList::getEndLine() const {
	return lines.second;
}

std::shared_ptr<ASTNode> StmtList::buildTree() {
	// **IMPORTANT** Placeholder implementation to avoid compilation error.
	std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
		ASTNodeType::STATEMENT_LIST, this->lines.first, Utility::getASTNodeType(ASTNodeType::STATEMENT_LIST)
	);

	for (auto child : this->statements) {
		tree.get()->addChild(child);
	}

	return tree;
}