#include "StmtList.h"
#include <iostream>

StmtList::StmtList() {}

int StmtList::getStartLine() const {
	return 0;
	// Do sth
}

int StmtList::getEndLine() const {
	return 0;
	// Do sth
}

std::shared_ptr<ASTNode> StmtList::buildTree() {
	// **IMPORTANT** Placeholder implementation to avoid compilation error.
	std::shared_ptr<ASTNode> tree = std::make_shared<ASTNode>(
		ASTNodeType::STATEMENT_LIST, this->lines.first, Utility::getASTNodeType(ASTNodeType::STATEMENT_LIST)
	);

	return tree;
}