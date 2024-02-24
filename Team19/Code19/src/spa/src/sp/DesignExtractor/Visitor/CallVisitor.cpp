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

void CallVisitor::setParents(listnode contexts, std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager) {
	int size = contexts.size();
	for (int i = 0; i < size; i++) {
		std::shared_ptr<ASTNode> context = contexts[i];
		if (context->type == ASTNodeType::PROCEDURE) continue;
		ParentTExtractor parentExtractor(context, root, pkbWriterManager);
		parentExtractor.extract();
	}
	if (size > 0 && contexts[size - 1]->type != ASTNodeType::PROCEDURE) {
		ParentExtractor parentExtractor(contexts[size - 1], root, pkbWriterManager);
		parentExtractor.extract();
	}
}

void CallVisitor::addContext(std::shared_ptr<ASTNode> context) {
	// do nothing
}