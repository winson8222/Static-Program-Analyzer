#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"

ExpressionVisitor::ExpressionVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	if (!Utility::nodeIsExpression(root->type) && !Utility::nodeIsConditionalOperator(root->type)) {
		throw std::runtime_error("ERROR: RelExpressionVisitor root node type not supported");
	}
}

void ExpressionVisitor::visit() {
	depthFirstSearch(root);
	// To handle additional cases later
}


void ExpressionVisitor::depthFirstSearch(std::shared_ptr<ASTNode> node) {
	if (node->type == ASTNodeType::VARIABLE) {
		VariableExtractor variableExtractor(node, pkbWriterManager);
		variableExtractor.extract();
	}
	else if (node->type == ASTNodeType::CONSTANT) {
		ConstantExtractor constantExtractor(node, pkbWriterManager);
		constantExtractor.extract();
	}
	for (auto& child : node->children) {
		depthFirstSearch(child);
	}
}

void ArithmeticExpressionVisitor::depthFirstSearch(std::shared_ptr<ASTNode> node) {
	ExpressionVisitor::depthFirstSearch(node);
}