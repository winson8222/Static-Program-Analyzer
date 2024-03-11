#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"

ProcedureVisitor::ProcedureVisitor(std::shared_ptr<ASTNode> node, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(node, pkbWriterManager) {
	if (node->type != ASTNodeType::PROCEDURE) {
		throw std::invalid_argument("ProcedureVisitor - input node type must be of type PROCEDURE");
	}
	this->contexts = std::vector<std::shared_ptr<ASTNode>>();
	this->wasVisited = false;
}

void ProcedureVisitor::visit() {
	ProcedureExtractor extractor(this->root, this->pkbWriterManager);
	extractor.extract();
	// extract information of the procedure nodes: Done
	if (this->root->children.size() == 0) {
		return;
	}
	// TODO: Recursively visit the statement list node, then later recursively visit all statements
	if (this->root->children[0]->type != ASTNodeType::STATEMENT_LIST) {
		throw std::runtime_error("Procedure node does not have a statement list node");
	}
	if (this->root->children.size() != 1) {
		throw std::runtime_error("Procedure node has more than 1 child");
	}
	StatementListVisitor statementListVisitor(this->root->children[0], this->pkbWriterManager);
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