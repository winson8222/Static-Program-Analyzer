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
		// set the used context (parent and siblings of the variable node)
		variableVisitor.setUsedContext(usedContexts, node); 
		variableVisitor.visit();
	}
	else if (node->type == ASTNodeType::CONSTANT) {
		ConstantExtractor constantExtractor(node, pkbWriterManager->getConstantWriter());
		constantExtractor.extract();
	}
	for (auto& child : node->getChildren()) {
		depthFirstSearch(child);
	}
}

void ExpressionVisitor::setUsedContext(listnode contexts, std::shared_ptr<ASTNode> parent) {
	usedContexts = listnode(contexts.begin(), contexts.end());
	usedContexts.push_back(parent);
}

void ExpressionVisitor::handlePatternExtraction(std::shared_ptr<ASTNode> root, ASTNodeType caller) {
	// do nothing
	std::shared_ptr<ASTNode> variableNode = root->getChildByIndex(EXPR_LHS_INDEX);
	std::shared_ptr<ASTNode> expressionNode = root->getChildByIndex(EXPR_RHS_INDEX);
	if (ASTUtility::nodeIsTarget(caller, ASTNodeType::WHILE)) {
		WhilePatternExtractor whilePatternExtractor(root, variableNode, expressionNode, pkbWriterManager->getWhilePatternWriter());
		whilePatternExtractor.extract();
	}
	else if (ASTUtility::nodeIsTarget(caller, ASTNodeType::IF_ELSE_THEN)) {
		IfsPatternExtractor ifsPatternExtractor(root, variableNode, expressionNode, pkbWriterManager->getIfPatternWriter());
		ifsPatternExtractor.extract();
	}
}

void ArithmeticExpressionVisitor::depthFirstSearch(std::shared_ptr<ASTNode> node) {
	ExpressionVisitor::depthFirstSearch(node);
}