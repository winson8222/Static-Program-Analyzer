#pragma once

#include "ASTNode.h"
#include "sp/AST/ASTUtility.h"

/*
* Note: to be set as default lines later for refactored implementations (M2)
*/
static int DEFAULT_LINE_NUMBER = 0;

class ASTTraverser {
	/*
	* @brief Set the correct line numbers for the nodes in the AST
	* @return the last statement number
	* 
	* Algorithm explanations: This is a modification of in-order traversal adapted
	* to the requirements of the SPA project. The method is called recursively from
	* the start of the program and traverses the AST in a depth-first manner, setting
	* actual statement number for each node. The method returns the last statement number
	* and carrying forward the highest number in backtracking to the next recursive call.
	*/
public:
	static int setLineNumbers(std::shared_ptr<ASTNode> node, int lineNumber);

private:

	/*
	* @brief Process the statement list and set consecutive statement numbers to each statement
	* on in-order traversing, incrementing the statement number by each iteration.
	* @return the last statement number
	*/
	static int processStatementList(std::shared_ptr<ASTNode> node, int currentLineNumber);
};