#pragma once

#include "sp/ControlFlow/CFGNode.h"
#include "sp/AST/ASTNode.h"
#include "sp/AST/ASTUtility.h"

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
	* @brief Creates all control flow graphs based on the AST representation of the SIMPLE program.
	* 
	* @returns A pointer to a vector of all control flow graphs, each representing one procedure.
	*/
	std::shared_ptr<std::vector<std::shared_ptr<CFGNode>>> createControlFlowGraphs();

private:
	static const int STATEMENT_LIST_INDEX = 0;
	std::shared_ptr<ASTNode> root;
	std::shared_ptr<ASTNode> getStatementList(std::shared_ptr<ASTNode> node);
	std::shared_ptr<CFGNode> generateFromProcedure(std::shared_ptr<ASTNode> procedureNode);
	std::shared_ptr<CFGNode> generateFromStatementList(std::shared_ptr<ASTNode> statementListNode, std::shared_ptr<CFGNode> nextNode);
	std::shared_ptr<CFGNode> generateFromStatement(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode);
	std::shared_ptr<CFGNode> generateFromIfElseThen(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode);
	std::shared_ptr<CFGNode> generateFromWhile(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode);
};
