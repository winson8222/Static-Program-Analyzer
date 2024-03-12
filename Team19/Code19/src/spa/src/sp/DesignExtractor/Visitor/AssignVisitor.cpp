#include "sp/DesignExtractor/Visitor/AssignVisitor.h"

AssignVisitor::AssignVisitor(std::shared_ptr<ASTNode> root, 
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (root->type != ASTNodeType::ASSIGN) {
		throw std::invalid_argument("ERROR: AssignVisitor - not an assign node");
	}
	this->contexts = listnode(context.begin(), context.end());
	this->lhsExpr = root->getChildByIndex(ASSIGN_LHS);
	this->rhsExpr = root->getChildByIndex(ASSIGN_RHS);
}

// assign (statement): extracts Assign (assign, statement, pattern)
// Variable, Constant (by lhs var + rhs expr), Uses, Modifies (lhs var)
void AssignVisitor::visit() {
	// TODO
	AssignExtractor assignExtractor(this->root, this->pkbWriterManager->getAssignWriter());
	assignExtractor.extract();

	VariableVisitor variableVisitor(lhsExpr, this->pkbWriterManager);
	variableVisitor.setModifiedContext(this->contexts, this->root);
	variableVisitor.visit();

	ArithmeticExpressionVisitor expressionVisitor(rhsExpr, this->pkbWriterManager);
	expressionVisitor.setUsedContext(this->contexts, this->root);
	expressionVisitor.visit();

	AssignPatternExtractor assignPatternExtractor(this->root, lhsExpr, rhsExpr, this->pkbWriterManager->getAssignPatternWriter());
	assignPatternExtractor.extract();

	setParents(this->contexts, this->root, this->pkbWriterManager);
}
