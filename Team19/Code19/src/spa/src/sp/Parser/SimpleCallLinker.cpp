#include "SimpleCallLinker.h"
#include <stdexcept>

SimpleCallLinker::SimpleCallLinker(std::shared_ptr<ASTNode> root) {
	this->root = root;
	for (auto child : root->getChildren()) {
	 	procedureNameToProcedureNode[child->getValue()] = child;
	}
}

void SimpleCallLinker::linkAllCallsToProcedure() {
	depthFirstSearch(root);
}

void SimpleCallLinker::depthFirstSearch(std::shared_ptr<ASTNode> node) {
	if (ASTUtility::nodeIsCall(node->getType())) {
		std::string procName = getProcedureVariableName(node->getChildByIndex(0));
		if (procedureNameToProcedureNode.find(procName) != procedureNameToProcedureNode.end()) {
			node->setChildByIndex(0, procedureNameToProcedureNode[procName]);
		} else {
			throw std::runtime_error("Procedure " + procName + " not found");
		}
	}
	for (auto child : node->getChildren()) {
		depthFirstSearch(child);
	}
}

std::string SimpleCallLinker::getProcedureVariableName(std::shared_ptr<ASTNode> node) {
	return node->getValue();
}