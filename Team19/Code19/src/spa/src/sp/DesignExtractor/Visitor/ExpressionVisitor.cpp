#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"

ExpressionVisitor::ExpressionVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	if (!ASTUtility::nodeCanFormValidExpression(root->type)) {
		throw std::invalid_argument("Invalid root node type for ExpressionVisitor");
	}
}

void ExpressionVisitor::visit() {
	depthFirstSearch(root);
}

void ExpressionVisitor::depthFirstSearch(std::shared_ptr<ASTNode> node) {
	if (node->type == ASTNodeType::VARIABLE) {
		VariableVisitor variableVisitor(node, this->pkbWriterManager);
		variableVisitor.setUsedContext(usedContexts, node); 
		// set the used context (parent and siblings of the variable node)
		variableVisitor.visit();
	}
	else if (node->type == ASTNodeType::CONSTANT) {
		ConstantExtractor constantExtractor(node, pkbWriterManager);
		constantExtractor.extract();
	}
	for (auto& child : node->children) {
		depthFirstSearch(child);
	}
}

void ExpressionVisitor::setUsedContext(listnode contexts, std::shared_ptr<ASTNode> parent) {
	usedContexts = listnode(contexts.begin(), contexts.end());
	usedContexts.push_back(parent);
}

void ArithmeticExpressionVisitor::depthFirstSearch(std::shared_ptr<ASTNode> node) {
	ExpressionVisitor::depthFirstSearch(node);
}