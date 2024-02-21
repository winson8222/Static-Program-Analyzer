#include "sp/DesignExtractor/Visitor/VariableVisitor.h"

void VariableVisitor::visit() {
	VariableExtractor variableExtractor(root, this->pkbWriterManager);
	variableExtractor.extract();

	/*
	UsesExtractor usesExtractor(this->root, this->contexts, this->pkbWriterManager);
	usesExtractor.extract();

	ModifiesExtractor modifiesExtractor(this->root, this->contexts, this->pkbWriterManager);
	modifiesExtractor.extract();
	*/
}

void VariableVisitor::setContext(std::vector<std::shared_ptr<ASTNode>> contexts, std::shared_ptr<ASTNode> parent) {
	this->contexts = std::vector<std::shared_ptr<ASTNode>>(contexts.begin(), contexts.end());
	this->contexts.push_back(parent);
}