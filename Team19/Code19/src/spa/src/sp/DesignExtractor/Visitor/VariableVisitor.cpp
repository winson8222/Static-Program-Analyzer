#include "sp/DesignExtractor/Visitor/VariableVisitor.h"

VariableVisitor::VariableVisitor(std::shared_ptr<ASTNode> root,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	if (!root->equalType(ASTNodeType::VARIABLE)) {
		throw std::invalid_argument("ERROR: VARIABLE NOT SUPPORTED");
	}
}

void VariableVisitor::visit() {
	VariableExtractor variableExtractor(root, this->pkbWriterManager->getVariableWriter());
	variableExtractor.extract();

	for (std::shared_ptr<ASTNode> context : usedContexts) {
		if (context->equalType(ASTNodeType::PROCEDURE)) {
			UsesPExtractor usesPExtractor(context, root, this->pkbWriterManager->getUsesPWriter());
			usesPExtractor.extract();
		}
		else {
			UsesSExtractor usesExtractor(context, root, this->pkbWriterManager->getUsesSWriter());
			usesExtractor.extract();
		}
	}
	
	for (std::shared_ptr<ASTNode> context : modifiedContexts) {
		if (context->equalType(ASTNodeType::PROCEDURE)) {
			ModifiesPExtractor modifiesPExtractor(context, root, this->pkbWriterManager->getModifiesPWriter());
			modifiesPExtractor.extract();
		}
		else {
			ModifiesSExtractor modifiesExtractor(context, root, this->pkbWriterManager->getModifiesSWriter());
			modifiesExtractor.extract();
		}
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