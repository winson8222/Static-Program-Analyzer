#include "ASTHelper.h"
#include <iostream>

int ASTHelper::setLineNumbers(std::shared_ptr<ASTNode> node, int lineNumber) {
	auto currentType = node->type;
	int currentLineNumber = lineNumber;
	node->lineNumber = currentLineNumber;

	// main case: statement list
	if (currentType == ASTNodeType::STATEMENT_LIST) {
		currentLineNumber = processStatementList(node, currentLineNumber);
	} // edge case: IF is handled separately as it has 2 statementlist child
	else if (currentType == ASTNodeType::IF_ELSE_THEN) {
		currentLineNumber = lineNumber;
		setLineNumbers(node->children[0], currentLineNumber);
		currentLineNumber = processStatementList(node->children[1], currentLineNumber);
		currentLineNumber = processStatementList(node->children[2], currentLineNumber);
	} // WHILE case are assumed to be handled same way as others
	else {
		for (auto& child : node->children) {
			currentLineNumber = setLineNumbers(child, lineNumber);
		}
	}
	return currentLineNumber;
}


int ASTHelper::processStatementList(std::shared_ptr<ASTNode> node, int currentLineNumber) {
	int newLineNumber = currentLineNumber;
	for (int i = 0; i < node->children.size(); i++) {
		auto& child = node->children[i];
		newLineNumber++;
		newLineNumber = setLineNumbers(child, newLineNumber);
	}
	return newLineNumber;
}

