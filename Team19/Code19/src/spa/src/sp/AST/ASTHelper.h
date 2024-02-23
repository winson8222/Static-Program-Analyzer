#pragma once

#include "ASTNode.h"
#include "sp/Utility.h"

/*
* Note: to be set as default lines later for refactored implementations (M2)
*/
static int DEFAULT_LINE_NUMBER = 0;

class ASTHelper {
	/*
	* @brief Set the correct line numbers for the nodes in the AST
	* @return the last line number
	* Algorithm explanations: Starts with 0 instead
	* 
	*/
public:
	static int setLineNumbers(
		std::shared_ptr<ASTNode> node, int lineNumber);
private:
	static int processStatementList(std::shared_ptr<ASTNode> node, int currentLineNumber);
};