#include "sp/DesignExtractor/Visitor/ExpressionVisitor.h"

ExpressionVisitor::ExpressionVisitor(std::shared_ptr<ASTNode> root, ASTNodeType caller, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	if (!ASTUtility::nodeCanFormValidExpression(root->getType())) {
		throw std::invalid_argument("Invalid root node type for ExpressionVisitor");
	}
	this->caller = caller;
}

void ExpressionVisitor::visit() {
	depthFirstSearch(root);
}

void ExpressionVisitor::depthFirstSearch(std::shared_ptr<ASTNode> node) {
	if (node->equalType(ASTNodeType::VARIABLE)) {
		handleVariableVisitor(node);
		handlePatternExtraction(node);
	}
	else if (node->equalType(ASTNodeType::CONSTANT)) {
		handleConstantExt(node);
	}
	for (auto& child : node->getChildren()) {
		depthFirstSearch(child);
	}
}

void ExpressionVisitor::setUsedContext(listnode contexts, std::shared_ptr<ASTNode> parent) {
	usedContexts = listnode(contexts.begin(), contexts.end());
	usedContexts.push_back(parent);
}

void ExpressionVisitor::handlePatternExtraction(std::shared_ptr<ASTNode> variableNode) {
	if (ASTUtility::nodeIsTarget(caller, ASTNodeType::WHILE)) {
		WhilePatternExtractor whilePatternExtractor(root, variableNode, pkbWriterManager->getWhilePatternWriter());
		whilePatternExtractor.extract();
	}
	else if (ASTUtility::nodeIsTarget(caller, ASTNodeType::IF_ELSE_THEN)) {
		IfsPatternExtractor ifsPatternExtractor(root, variableNode, pkbWriterManager->getIfPatternWriter());
		ifsPatternExtractor.extract();
	}
	// do nothing otherwise
}

// set the used context (parent and siblings of the variable node)
void ExpressionVisitor::handleVariableVisitor(std::shared_ptr<ASTNode> variableNode) {
	VariableVisitor variableVisitor(variableNode, this->pkbWriterManager);
	variableVisitor.setUsedContext(usedContexts, variableNode);
	variableVisitor.visit();
}

void ExpressionVisitor::handleConstantExt(std::shared_ptr<ASTNode> constantNode) {
	ConstantExtractor constantExtractor(constantNode, pkbWriterManager->getConstantWriter());
	constantExtractor.extract();
}

void ArithmeticExpressionVisitor::depthFirstSearch(std::shared_ptr<ASTNode> node) {
	ExpressionVisitor::depthFirstSearch(node);
}
