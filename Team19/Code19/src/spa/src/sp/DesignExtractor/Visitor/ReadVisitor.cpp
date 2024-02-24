#include "sp/DesignExtractor/Visitor/ReadVisitor.h"

ReadVisitor::ReadVisitor(std::shared_ptr<ASTNode> root,
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (root->type != ASTNodeType::READ) {
		throw std::invalid_argument("ReadVisitor - root is not of type PRINT");
	}
	if (root->children.size() != 1) {
		throw std::invalid_argument("ReadVisitor - root does not have 1 child");
	}
	this->contexts = listnode(context.begin(), context.end());
}

void ReadVisitor::visit() {
	ReadExtractor readExtractor(this->root, this->pkbWriterManager);
	readExtractor.extract();

	VariableVisitor variableVisitor(this->root->children[0], this->pkbWriterManager);
	variableVisitor.setModifiedContext(this->contexts, this->root);
	variableVisitor.visit();

	setParents(this->contexts, this->root, this->pkbWriterManager);
}

void ReadVisitor::setParents(listnode contexts, std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager) {
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

void ReadVisitor::addContext(std::shared_ptr<ASTNode> node) {
	// do nothing
}