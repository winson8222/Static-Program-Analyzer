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
	explicit SimpleControlFlow(std::shared_ptr<ASTNode> root);

	/*
	* @brief Creates all control flow graphs based on the AST representation of the SIMPLE program.
	* 
	* @returns A pointer to a vector of all control flow graphs, each representing one procedure.
	*/
	std::shared_ptr<std::vector<std::shared_ptr<CFGNode>>> createControlFlowGraphs();

private:
	static const int PROCEDURE_STATEMENT_LIST_INDEX = 0;
	static const int WHILE_STATEMENT_LIST_INDEX = 1;
	static const int IF_STATEMENT_LIST_INDEX = 1;
	static const int ELSE_STATEMENT_LIST_INDEX = 2;
	std::shared_ptr<ASTNode> root;
	std::shared_ptr<ASTNode> getStatementList(std::shared_ptr<ASTNode> node, int index);
	std::shared_ptr<CFGNode> generateFromProcedure(std::shared_ptr<ASTNode> procedureNode);
	std::shared_ptr<CFGNode> generateFromStatementList(std::shared_ptr<ASTNode> statementListNode, std::shared_ptr<CFGNode> nextNode);
	std::shared_ptr<CFGNode> generateFromStatement(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode);
	std::shared_ptr<CFGNode> generateFromIfElseThen(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode);
	std::shared_ptr<CFGNode> generateFromWhile(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode);
};
