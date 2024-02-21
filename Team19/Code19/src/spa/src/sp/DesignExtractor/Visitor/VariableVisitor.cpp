#include "sp/DesignExtractor/Visitor/VariableVisitor.h"

void VariableVisitor::visit() {
	VariableExtractor variableExtractor(root, this->pkbWriterManager);
	variableExtractor.extract();

	for (std::shared_ptr<ASTNode> context : usedContexts) {
		UsesExtractor usesExtractor(context, root, this->pkbWriterManager);
		usesExtractor.extract();
	}
	
	for (std::shared_ptr<ASTNode> context : modifiedContexts) {
		ModifiesExtractor modifiesExtractor(root, context, this->pkbWriterManager);
		modifiesExtractor.extract();
	}
}

void VariableVisitor::setUsedContext(listnode contexts, std::shared_ptr<ASTNode> parent) {
	//this->contexts = contexts;
	usedContexts = listnode(contexts.begin(), contexts.end());
	usedContexts.push_back(parent);
}

void VariableVisitor::setModifiedContext(listnode contexts, std::shared_ptr<ASTNode> parent) {
	//this->contexts = contexts;
	modifiedContexts = listnode(contexts.begin(), contexts.end());
	modifiedContexts.push_back(parent);
}