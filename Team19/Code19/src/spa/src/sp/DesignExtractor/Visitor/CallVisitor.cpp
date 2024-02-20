#include "sp/DesignExtractor/Visitor/CallVisitor.h"

void CallVisitor::visit() {
	// TODO
	CallExtractor callExtractor(this->root, this->pkbWriterManager);
	callExtractor.extract();

	VariableExtractor variableExtractor(this->root->children[0], this->pkbWriterManager);
	variableExtractor.extract();

	int size = contexts.size();
	for (int i = 0; i < size; i++) {
		std::shared_ptr<ASTNode> context = contexts[i];
		if (context->type == ASTNodeType::PROCEDURE) continue;
		ParentTExtractor parentExtractor(context, root, pkbWriterManager);
		parentExtractor.extract();
	}
	if (size > 0) {
		ParentExtractor parentExtractor(contexts[size - 1], root, pkbWriterManager);
		parentExtractor.extract();
	}
}

void CallVisitor::addContext(std::shared_ptr<ASTNode> context) {
	// do nothing
}