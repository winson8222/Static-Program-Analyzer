#include "sp/DesignExtractor/Visitor/CallVisitor.h"

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

	ProcedureExtractor procExt(this->root->children[0], this->pkbWriterManager);
	procExt.extract();

	setParents(this->contexts, this->root, this->pkbWriterManager);
}

void CallVisitor::addContext(std::shared_ptr<ASTNode> context) {
	// do nothing
}