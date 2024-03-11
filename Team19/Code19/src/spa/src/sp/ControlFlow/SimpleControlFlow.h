#pragma once

#include "sp/ControlFlow/CFGNode.h"
#include "sp/AST/ASTNode.h"
#include <unordered_map>

/*
* @brief This class is used to generate a CFG Representation of the source SIMPLE program.
*/
class SimpleControlFlow {
public:
	/*
	* @brief Constructor for Control Flow Graph generator that takes in the root of the AST.
	*/
	SimpleControlFlow(std::shared_ptr<ASTNode> root);

	/*
	* @brief Creates the control flow graph based on the AST representation of the SIMPLE program.
	*/
	std::shared_ptr<CFGNode> createControlFlowGraph();
private:
	std::shared_ptr<ASTNode> root;
};
