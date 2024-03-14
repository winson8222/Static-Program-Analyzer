#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"

ProcedureVisitor::ProcedureVisitor(std::shared_ptr<ASTNode> node, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(node, pkbWriterManager) {
	if (!ASTUtility::nodeIsTarget(node->type, ASTNodeType::PROCEDURE)) {
		throw std::invalid_argument("ProcedureVisitor - input node type must be of type PROCEDURE");
	}
	this->contexts = std::vector<std::shared_ptr<ASTNode>>();
	this->wasVisited = false;
	this->statementListNode = node->getChildByIndex(PROCEDURE_STATEMENT_LIST_INDEX);
	if (!this->statementListNode->equalType(ASTNodeType::STATEMENT_LIST)) {
		throw std::invalid_argument("ProcedureVisitor - statement list node must be of type STATEMENT_LIST");
	}
}

void ProcedureVisitor::visit() {
	handleProcedureExtractor();
	handleStatementListVisitor();
	handleControlFlowGraph();
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

void ProcedureVisitor::handleProcedureExtractor() {
	ProcedureExtractor extractor(this->root, this->pkbWriterManager->getProcedureWriter());
	extractor.extract();
}

void ProcedureVisitor::handleStatementListVisitor() {
	StatementListVisitor statementListVisitor(statementListNode, this->pkbWriterManager);
	statementListVisitor.setContext(contexts, root);
	statementListVisitor.visit();
}

void ProcedureVisitor::handleControlFlowGraph() {
	SimpleControlFlow cfg(this->root);
	std::vector<std::shared_ptr<CFGNode>> cfgGraphs = *(cfg.createControlFlowGraphs());
	CFGVisitor cfgVisitor(cfgGraphs, this->pkbWriterManager);
	cfgVisitor.visit();
}