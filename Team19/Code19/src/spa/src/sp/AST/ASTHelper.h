#pragma once

#include "ASTNode.h"
#include "sp/Utility.h"

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
};