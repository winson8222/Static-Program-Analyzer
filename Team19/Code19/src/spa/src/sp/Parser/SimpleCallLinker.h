#pragma once

#include <unordered_map>
#include "sp/AST/ASTNode.h"
#include "sp/AST/ASTUtility.h"

/*
* This class is used to link all calls to procedures to the procedure node.
*/
class SimpleCallLinker {
public:
	/*
	* Constructor for SimpleCallLinker that takes in the root of the AST.
	*/
	explicit SimpleCallLinker(std::shared_ptr<ASTNode> root);

	/*
	* Links all calls to procedures to the procedure node.
	*/
	void linkAllCallsToProcedure();

private:
	std::string getProcedureVariableName(std::shared_ptr<ASTNode> node);
	/*
	* Depth first search to link all calls to procedures to the procedure node
	*/
	void depthFirstSearch(std::shared_ptr<ASTNode> root);

	/*
	* A hash map that map the procedure name to the procedure node.
	*/
	std::unordered_map<std::string, std::shared_ptr<ASTNode>> procedureNameToProcedureNode;

	/*
	* The root of the AST.
	*/
	std::shared_ptr<ASTNode> root;
};
