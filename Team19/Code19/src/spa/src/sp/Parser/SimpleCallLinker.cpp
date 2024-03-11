#include "SimpleCallLinker.h"
#include <iostream>
#include <stdexcept>

SimpleCallLinker::SimpleCallLinker(std::shared_ptr<ASTNode> root) {
	this->root = root;
	for (auto child : root->children) {
	 	procedureNameToProcedureNode[child->value] = child;
	}
}

void SimpleCallLinker::linkAllCallsToProcedure() {
	depthFirstSearch(root);
}

void SimpleCallLinker::depthFirstSearch(std::shared_ptr<ASTNode> node) {
	if (ASTUtility::nodeIsCall(node->type)) {
		std::string procName = node->children[0]->value;
		if (procedureNameToProcedureNode.find(procName) != procedureNameToProcedureNode.end()) {
			node->children[0] = procedureNameToProcedureNode[procName];
		} else {
			throw std::runtime_error("Procedure " + procName + " not found");
		}
	}
	for (auto child : node->children) {
		depthFirstSearch(child);
	}
}