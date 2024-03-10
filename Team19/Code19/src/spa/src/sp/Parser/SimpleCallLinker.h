#pragma once

#include "sp/AST/ASTNode.h"
#include "sp/AST/ASTUtility.h"
#include <unordered_map>

class SimpleCallLinker {
public:
	SimpleCallLinker(std::shared_ptr<ASTNode> root);
	void linkAllCallsToProcedure();

private:
	void depthFirstSearch(std::shared_ptr<ASTNode> root);
	std::unordered_map<std::string, std::shared_ptr<ASTNode>> procedureNameToProcedureNode;
	std::shared_ptr<ASTNode> root;
};
