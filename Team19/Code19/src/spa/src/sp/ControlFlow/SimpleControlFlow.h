#pragma once

#include "sp/AST/ASTNode.h"
#include "sp/AST/ASTUtility.h"
#include <unordered_map>

/*
* This class is used to link all calls to procedures to the procedure node.
*/
class SimpleControlFlow {
public:
	/*
	* Constructor for Control Flow Graph generator that takes in the root of the AST.
	*/
	SimpleControlFlow(std::shared_ptr<ASTNode> root);

	/*
	* Links all calls to procedures to the procedure node.
	*/
	std::shared_ptr<CFGNode> createControlFlowGraph();
private:
	std::shared_ptr<ASTNode> root;
};
