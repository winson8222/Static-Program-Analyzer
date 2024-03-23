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
	for (auto value : this->contexts) {
		if (value->equalType(ASTNodeType::PROCEDURE)) {
			procedureContexts.push_back(value);
			mostRecentProcedure = value;
			handleCallsT(value, calleeProcedure);
		}
		else if (value->equalType(value->getType())) {
			procedureContexts.push_back(value);
		}
	}

	handleCallsP(mostRecentProcedure, calleeProcedure);
	procedureContexts.push_back(this->root);
	return procedureContexts;
}

void CallVisitor::handleCallExtractor() {
	CallExtractor callExtractor(this->root, this->pkbWriterManager->getCallWriter());
	callExtractor.extract();
}

void CallVisitor::handleCallProcNameExtractor() {
	CallProcNameExtractor callProcNameExtractor(this->root, this->procNode, this->pkbWriterManager->getCallProcNameWriter());
	callProcNameExtractor.extract();
}

void CallVisitor::handleCallsP(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	CallsPExtractor callsPExtractor(ast1, ast2, this->pkbWriterManager->getCallsWriter());
	callsPExtractor.extract();
}

void CallVisitor::handleCallsT(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	CallsTExtractor callsTExtractor(ast1, ast2, this->pkbWriterManager->getCallsTWriter());
	callsTExtractor.extract();
}
