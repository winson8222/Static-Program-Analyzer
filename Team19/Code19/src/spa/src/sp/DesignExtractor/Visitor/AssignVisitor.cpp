#include "sp/DesignExtractor/Visitor/AssignVisitor.h"

AssignVisitor::AssignVisitor(std::shared_ptr<ASTNode> root, 
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (root->type != ASTNodeType::ASSIGN) {
		throw std::invalid_argument("ERROR: AssignVisitor - not an assign node");
	}
	this->contexts = listnode(context.begin(), context.end());
}

// assign (statement): extracts Assign (assign, statement, pattern)
// Variable, Constant (by lhs var + rhs expr), Uses, Modifies (lhs var)
void AssignVisitor::visit() {
	// TODO
	AssignExtractor assignExtractor(this->root, this->pkbWriterManager);
	assignExtractor.extract();

	VariableVisitor variableVisitor(this->root->children[0], this->contexts, this->pkbWriterManager);
	variableVisitor.visit();

	ArithmeticExpressionVisitor expressionVisitor(this->root->children[1], this->pkbWriterManager);
	expressionVisitor.visit();

	int size = contexts.size();
	for (int i = 0; i < size; i++) {
		std::shared_ptr<ASTNode> context = contexts[i];
		if (context->type == ASTNodeType::PROCEDURE) continue;
		ParentTExtractor parentExtractor(context, root, pkbWriterManager);
		parentExtractor.extract();
	}
	if (size > 0) {
		ParentExtractor parentExtractor(contexts[size - 1], root, pkbWriterManager);
		parentExtractor.extract();
	}
}

void AssignVisitor::addContext(std::shared_ptr<ASTNode> context) {
	// Do nothing
}