#include "ASTHelper.h"
#include <iostream>

int ASTTraverser::setLineNumbers(std::shared_ptr<ASTNode> node, int lineNumber) {
	auto currentType = node->type;
	int currentLineNumber = lineNumber;
	node->lineNumber = currentLineNumber;

	// main case: statement list
	if (ASTUtility::nodeIsStatementList(currentType)) {
		currentLineNumber = processStatementList(node, currentLineNumber);
	} 
	// edge case: IF is handled separately as it has 2 statementlist child
	else if (ASTUtility::nodeIsIfElse(currentType)) {
		currentLineNumber = lineNumber;
		setLineNumbers(node->children[0], currentLineNumber);
		currentLineNumber = processStatementList(node->children[1], currentLineNumber);
		currentLineNumber = processStatementList(node->children[2], currentLineNumber);
	} 
	// WHILE case are assumed to be handled same way as others
	// else keep the same line number for all children, carrying forward.
	else {
		for (auto& child : node->children) {
			currentLineNumber = setLineNumbers(child, lineNumber);
		}
	}
	return currentLineNumber;
}


int ASTTraverser::processStatementList(std::shared_ptr<ASTNode> node, int currentLineNumber) {
	int newLineNumber = currentLineNumber;
	for (int i = 0; i < node->children.size(); i++) {
		auto& child = node->children[i];
		newLineNumber++;
		newLineNumber = setLineNumbers(child, newLineNumber);
	}
	return newLineNumber;
}

