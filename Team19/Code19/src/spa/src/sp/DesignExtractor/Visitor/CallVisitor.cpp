#include "sp/DesignExtractor/Visitor/CallVisitor.h"
#include <iostream>

CallVisitor::CallVisitor(std::shared_ptr<ASTNode> root,
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	this->contexts = listnode(context.begin(), context.end());
}

void CallVisitor::visit() {
	// TODO
	CallExtractor callExtractor(this->root, this->pkbWriterManager);
	callExtractor.extract();

	ProcedureVisitor procedureVisitor(this->root->children[0], this->pkbWriterManager);
	procedureVisitor.addContexts(getProcedureContexts());
	procedureVisitor.visit();
	procedureVisitor.setIsVisited();

	setParents(this->contexts, this->root, this->pkbWriterManager);
}

std::vector<std::shared_ptr<ASTNode>> CallVisitor::getProcedureContexts() {
	// to set context of previous procedure call later by iterating through the list
	std::vector<std::shared_ptr<ASTNode>> procedureContexts;
	for (auto value : this->contexts) {
		if (ASTUtility::nodeIsProcedure(value->type)) {
			procedureContexts.push_back(value);
		}
	}
	procedureContexts.push_back(this->root);
	return procedureContexts;
}
