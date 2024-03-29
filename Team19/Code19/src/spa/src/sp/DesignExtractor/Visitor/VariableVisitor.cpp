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
	UsesPExtractor usesPExtractor(user, variable, this->pkbWriterManager->getUsesPWriter());
	usesPExtractor.extract();
}

void VariableVisitor::handleUsesS(std::shared_ptr<ASTNode> user, std::shared_ptr<ASTNode> variable) {
	UsesSExtractor usesExtractor(user, variable, this->pkbWriterManager->getUsesSWriter());
	usesExtractor.extract();
}

void VariableVisitor::handleModifiesP(std::shared_ptr<ASTNode> user, std::shared_ptr<ASTNode> variable) {
	ModifiesPExtractor modifiesPExtractor(user, variable, this->pkbWriterManager->getModifiesPWriter());
	modifiesPExtractor.extract();
}

void VariableVisitor::handleModifiesS(std::shared_ptr<ASTNode> user, std::shared_ptr<ASTNode> variable) {
	ModifiesSExtractor modifiesExtractor(user, variable, this->pkbWriterManager->getModifiesSWriter());
	modifiesExtractor.extract();
}
