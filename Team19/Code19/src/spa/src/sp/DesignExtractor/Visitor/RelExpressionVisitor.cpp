#include "sp/DesignExtractor/Visitor/RelExpressionVisitor.h"

RelExpressionVisitor::RelExpressionVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	// for now, do nothing
	if (!Utility::nodeIsExpression(root->type) && !Utility::nodeIsConditionalOperator) {
		throw std::runtime_error("ERROR: RelExpressionVisitor root node type not supported");
	}
}

void RelExpressionVisitor::visit() {
	depthFirstSearch(root);
	// Later, we will need to handle Uses relations here
	/*
		if (Utility::nodeIsExpression(root->type)) {

		}
		else if (Utility::nodeIsConditionalOperator(root->type)) {
			// for now, do nothing
		}
		else {
			throw std::runtime_error("ERROR: RelExpressionVisitor node type not supported");
		}
	*/
}

void RelExpressionVisitor::visit(std::shared_ptr<ASTNode> node) {
	
}

void RelExpressionVisitor::depthFirstSearch(std::shared_ptr<ASTNode> node) {
	std::cout << "DFS called for " << Utility::getASTNodeType(node->type) << std::endl;
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