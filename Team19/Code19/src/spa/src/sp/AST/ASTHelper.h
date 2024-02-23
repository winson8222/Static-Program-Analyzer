#include "ASTNode.h"

class ASTHelper {
	/*
	* @brief Set the correct line numbers for the nodes in the AST
	* 
	* Algorithm explanations:
	* 
	*/
	static void setCorrectLineNumbers(ASTNode* node, int lineNumber) {
		node->setLineNumber(lineNumber);
		for (auto child : node->getChildren()) {
			setCorrectLineNumbers(child, lineNumber);
		}
	}
};