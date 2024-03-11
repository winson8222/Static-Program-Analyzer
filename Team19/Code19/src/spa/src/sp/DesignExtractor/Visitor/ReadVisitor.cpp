#include "sp/DesignExtractor/Visitor/ReadVisitor.h"

ReadVisitor::ReadVisitor(std::shared_ptr<ASTNode> root,
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (!root->equalType(ASTNodeType::READ)) {
		throw std::invalid_argument("ReadVisitor - root is not of type READ");
	}
	this->contexts = listnode(context.begin(), context.end());
}

void ReadVisitor::visit() {
	ReadExtractor readExtractor(this->root, this->pkbWriterManager->getReadWriter());
	readExtractor.extract();

	VariableVisitor variableVisitor(this->root->getChildByIndex(0), this->pkbWriterManager);
	variableVisitor.setModifiedContext(this->contexts, this->root);
	variableVisitor.visit();

	setParents(this->contexts, this->root, this->pkbWriterManager);
}