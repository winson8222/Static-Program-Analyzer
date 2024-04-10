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
			handleUsesP(context, root);
		}
		else {
			handleUsesS(context, root);
		}
	}
	
	for (std::shared_ptr<ASTNode> context : modifiedContexts) {
		if (context->equalType(ASTNodeType::PROCEDURE)) {
			handleModifiesP(context, root);
		}
		else {
			handleModifiesS(context, root);
		}
	}
}

void VariableVisitor::setUsedContext(listnode contexts, std::shared_ptr<ASTNode> parent) {
	usedContexts = listnode(contexts.begin(), contexts.end());
	usedContexts.push_back(parent);
}

void VariableVisitor::setModifiedContext(listnode contexts, std::shared_ptr<ASTNode> parent) {
	modifiedContexts = listnode(contexts.begin(), contexts.end());
	modifiedContexts.push_back(parent);
}

void VariableVisitor::handleUsesP(std::shared_ptr<ASTNode> user, std::shared_ptr<ASTNode> variable) {
	UsesPExtractor usesPExtractor(this->pkbWriterManager->getUsesPWriter());
	usesPExtractor.extract(user, variable);
}

void VariableVisitor::handleUsesS(std::shared_ptr<ASTNode> user, std::shared_ptr<ASTNode> variable) {
	UsesSExtractor usesExtractor(this->pkbWriterManager->getUsesSWriter());
	usesExtractor.extract(user, variable);
}

void VariableVisitor::handleModifiesP(std::shared_ptr<ASTNode> user, std::shared_ptr<ASTNode> variable) {
	ModifiesPExtractor modifiesPExtractor(this->pkbWriterManager->getModifiesPWriter());
	modifiesPExtractor.extract(user, variable);
}

void VariableVisitor::handleModifiesS(std::shared_ptr<ASTNode> user, std::shared_ptr<ASTNode> variable) {
	ModifiesSExtractor modifiesExtractor(this->pkbWriterManager->getModifiesSWriter());
	modifiesExtractor.extract(user, variable);
}
