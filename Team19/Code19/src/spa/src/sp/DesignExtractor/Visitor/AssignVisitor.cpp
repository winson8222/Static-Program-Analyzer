#include "sp/DesignExtractor/Visitor/AssignVisitor.h"

AssignVisitor::AssignVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, pkbWriterManager) {
	if (root->type != ASTNodeType::ASSIGN) {
		throw std::invalid_argument("ERROR: AssignVisitor - not an assign node");
	}
}

// assign (statement): extracts Assign (assign, statement, pattern)
// Variable, Constant (by lhs var + rhs expr), Uses, Modifies (lhs var)
void AssignVisitor::visit() {
	// TODO
	AssignExtractor assignExtractor(this->root, this->pkbWriterManager);
	assignExtractor.extract();

	VariableExtractor variableExtractor(this->root->children[0], this->pkbWriterManager);
	variableExtractor.extract();

	ArithmeticExpressionVisitor expressionVisitor(this->root->children[1], this->pkbWriterManager);
	expressionVisitor.visit();
}