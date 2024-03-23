#include "sp/DesignExtractor/Visitor/AssignVisitor.h"

AssignVisitor::AssignVisitor(std::shared_ptr<ASTNode> root,
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (!root->equalType(ASTNodeType::ASSIGN)) {
		throw std::invalid_argument("ERROR: AssignVisitor - not an assign node");
	}

	this->contexts = listnode(context.begin(), context.end());
	this->lhsExpr = root->getChildByIndex(ASSIGN_LHS);
	this->rhsExpr = root->getChildByIndex(ASSIGN_RHS);
}

// assign (statement): extracts Assign (assign, statement, pattern)
// Variable, Constant (by lhs var + rhs expr), Uses, Modifies (lhs var)
void AssignVisitor::visit() {
	handleAssignExtraction(this->root);
	handleLHSExtraction(this->lhsExpr);
	handleRHSExtraction(this->rhsExpr);
	handleAssignPatternExtraction(this->root, this->lhsExpr, this->rhsExpr);
}

void AssignVisitor::handleAssignExtraction(std::shared_ptr<ASTNode> node) {
	AssignExtractor assignExtractor(node, this->pkbWriterManager->getAssignWriter());
	assignExtractor.extract();
}

void AssignVisitor::handleLHSExtraction(std::shared_ptr<ASTNode> node) {
	VariableVisitor variableVisitor(node, this->pkbWriterManager);
	variableVisitor.setModifiedContext(this->contexts, this->root);
	variableVisitor.visit();
}

void AssignVisitor::handleRHSExtraction(std::shared_ptr<ASTNode> node) {
	ExpressionVisitor expressionVisitor(node, ASTNodeType::ASSIGN, this->pkbWriterManager);
	expressionVisitor.setUsedContext(this->contexts, this->root);
	expressionVisitor.visit();
}

void AssignVisitor::handleAssignPatternExtraction(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2, std::shared_ptr<ASTNode> ast3) {
	AssignPatternExtractor assignPatternExtractor(ast1, ast2, ast3, this->pkbWriterManager->getAssignPatternWriter());
	assignPatternExtractor.extract();
}