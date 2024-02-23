#include "ASTHelper.h"
#include <iostream>

int ASTHelper::setLineNumbers(std::shared_ptr<ASTNode> node, int lineNumber) {
	auto currentType = node->type;

	int currentLineNumber = lineNumber;
	if (currentType == ASTNodeType::STATEMENT_LIST) {
		int size = node->children.size();
		node->lineNumber = currentLineNumber;
		for (int i = 0; i < size; i++) {
			auto& child = node->children[i];
			currentLineNumber++;
			currentLineNumber = setLineNumbers(child, currentLineNumber);
		}
	} 
	else if (currentType == ASTNodeType::IF_ELSE_THEN) {
		currentLineNumber = lineNumber;
		node->lineNumber = currentLineNumber;
		setLineNumbers(node->children[0], currentLineNumber);
		// process as with other cases

		auto thenStatements = node->children[1];
		thenStatements->lineNumber = lineNumber ;
		for (int i = 0; i < thenStatements->children.size(); i++) {
			auto& child = thenStatements->children[i];
			currentLineNumber++;
			currentLineNumber = setLineNumbers(child, currentLineNumber);
		}

		auto elseStatements = node->children[2];
		elseStatements->lineNumber = lineNumber;
		for (int i = 0; i < elseStatements->children.size(); i++) {
			auto& child = elseStatements->children[i];
			currentLineNumber++;
			currentLineNumber = setLineNumbers(child, currentLineNumber);
		}
	}
	else {
		node->lineNumber = currentLineNumber;
		for (auto& child : node->children) {
			currentLineNumber = setLineNumbers(child, lineNumber);
		}
	}
	return currentLineNumber;
}