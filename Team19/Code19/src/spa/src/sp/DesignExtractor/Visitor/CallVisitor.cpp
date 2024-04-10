#include "sp/DesignExtractor/Visitor/CallVisitor.h"

CallVisitor::CallVisitor(std::shared_ptr<ASTNode> root,
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	this->contexts = listnode(context.begin(), context.end());
	this->procNode = root->getChildByIndex(CALLS_VARIABLE_INDEX);
}

void CallVisitor::visit() {
	handleCallExtractor();
	handleCallProcNameExtractor();
	handleProcedureVisitor();
}

void CallVisitor::handleProcedureVisitor() {
	ProcedureVisitor procedureVisitor(this->procNode, this->pkbWriterManager);
	procedureVisitor.addContexts(getProcedureContexts());
	procedureVisitor.visit();
	procedureVisitor.setIsVisited();
}

std::vector<std::shared_ptr<ASTNode>> CallVisitor::getProcedureContexts() {
	// to set context of previous procedure call later by iterating through the list
	std::shared_ptr<ASTNode> mostRecentProcedure;
	std::shared_ptr<ASTNode> calleeProcedure = this->root->getChildByIndex(0);
	std::vector<std::shared_ptr<ASTNode>> procedureContexts;

	CallProcNameExtractor callProcNameExtractor(this->pkbWriterManager->getCallProcNameWriter());
	CallsPExtractor callsPExtractor(this->pkbWriterManager->getCallsWriter());
	CallsTExtractor callsTExtractor(this->pkbWriterManager->getCallsTWriter());

	for (std::shared_ptr<ASTNode> value : this->contexts) {
		if (value->equalType(ASTNodeType::PROCEDURE)) {
			procedureContexts.push_back(value);
			mostRecentProcedure = value;
			callsTExtractor.extract(value, calleeProcedure);
		}
		else if (value->equalType(value->getType())) {
			procedureContexts.push_back(value);
		}
	}

	callsPExtractor.extract(mostRecentProcedure, calleeProcedure);
	procedureContexts.push_back(this->root);
	return procedureContexts;
}

void CallVisitor::handleCallExtractor() {
	CallExtractor callExtractor(this->root, this->pkbWriterManager->getCallWriter());
	callExtractor.extract();
}

void CallVisitor::handleCallProcNameExtractor() {
	CallProcNameExtractor callProcNameExtractor(this->pkbWriterManager->getCallProcNameWriter());
	callProcNameExtractor.extract(this->root, this->procNode);
}
