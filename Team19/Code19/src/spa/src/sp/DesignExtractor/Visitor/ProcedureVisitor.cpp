#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"

ProcedureVisitor::ProcedureVisitor(std::shared_ptr<ASTNode> node, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(node, pkbWriterManager) {
	if (!ASTUtility::nodeIsTarget(node->type, ASTNodeType::PROCEDURE)) {
		throw std::invalid_argument("ProcedureVisitor - input node type must be of type PROCEDURE");
	}
	this->contexts = std::vector<std::shared_ptr<ASTNode>>();
	this->wasVisited = false;
	// this->statementListNode = this->root->getChildByIndex(PROCEDURE_STATEMENT_LIST_INDEX);
}

void ProcedureVisitor::visit() {
	ProcedureExtractor extractor(this->root, this->pkbWriterManager->getProcedureWriter());
	extractor.extract();

	std::vector<std::shared_ptr<ASTNode>> child = this->root->getChildren();

	// extract information of the procedure nodes: Done
	if (child.size() == 0) {
		return;
	}
	else if (child.size() > 1) {
		throw std::runtime_error("Procedure node has more than 1 child");
	}
	std::shared_ptr<ASTNode> target = this->root->getChildByIndex(0);
	if (target->getType() != ASTNodeType::STATEMENT_LIST) {
		return;
	}
	StatementListVisitor statementListVisitor(target, this->pkbWriterManager);
	statementListVisitor.setContext(contexts, root);
	statementListVisitor.visit();
}

void ProcedureVisitor::setIsVisited() {
	this->root->setVisited();
}

bool ProcedureVisitor::checkIfVisited() {
	return this->root->getVisited();
}

void ProcedureVisitor::addContexts(std::vector<std::shared_ptr<ASTNode>> contexts) {
	this->contexts.insert(this->contexts.end(), contexts.begin(), contexts.end());
}