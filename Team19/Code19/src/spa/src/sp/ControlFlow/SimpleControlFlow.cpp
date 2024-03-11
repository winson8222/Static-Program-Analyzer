#include "SimpleControlFlow.h"

SimpleControlFlow::SimpleControlFlow(std::shared_ptr<ASTNode> root) : root(root) {}

std::shared_ptr<std::vector<std::shared_ptr<CFGNode>>> SimpleControlFlow::createControlFlowGraphs() {
	std::vector<std::shared_ptr<ASTNode>> procedures = this->root->getChildren();

	std::shared_ptr<std::vector<std::shared_ptr<CFGNode>>> controlFlowGraphs = std::make_shared<std::vector<std::shared_ptr<CFGNode>>>();

	for (auto& procedure : procedures) {
		std::shared_ptr<CFGNode> procedureCfg = this->generateFromProcedure(procedure);
	}

	return controlFlowGraphs;
};

std::shared_ptr<ASTNode> SimpleControlFlow::getStatementList(std::shared_ptr<ASTNode> node, int index) {
	return node->getChildByIndex(index);
};

std::shared_ptr<CFGNode> SimpleControlFlow::generateFromProcedure(std::shared_ptr<ASTNode> procedureNode) {
	std::shared_ptr<ASTNode> statementListNode = this->getStatementList(procedureNode, PROCEDURE_STATEMENT_LIST_INDEX);
	std::shared_ptr<CFGNode> endOfProcedureDummyNode = CFGNode::getDummyNode()
	return this->generateFromStatementList(statementListNode, endOfProcedureDummyNode);
}

std::shared_ptr<CFGNode> SimpleControlFlow::generateFromStatementList(std::shared_ptr<ASTNode> statementListNode, std::shared_ptr<CFGNode> nextNode) {
	std::vector<std::shared_ptr<ASTNode>> statements = statementListNode->getChildren();

	// Recursively add the node representing the next line as a child opf the current node.
	for (int i = statements.size() - 1; i >= 0; i--) {
		std::shared_ptr<CFGNode> node = this->generateFromStatement(statements[i], nextNode);
		nextNode = node;
	}

	return nextNode;
}

std::shared_ptr<CFGNode> SimpleControlFlow::generateFromStatement(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode) {
	ASTNodeType nodeType = statementNode->getType();

	if (ASTUtility::nodeIsTarget(nodeType, ASTNodeType::IF_ELSE_THEN)) {	
		return this->generateFromIfElseThen(statementNode, nextNode);
	}
	else if (ASTUtility::nodeIsTarget(nodeType, ASTNodeType::WHILE)) {
		return this->generateFromWhile(statementNode, nextNode);
	}

	int lineNumber = statementNode->getLineNumber();
	std::shared_ptr<CFGNode> node = std::make_shared<CFGNode>(lineNumber);
	node->addChild(nextNode);
	
	return node;
}

std::shared_ptr<CFGNode> SimpleControlFlow::generateFromIfElseThen(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode) {
	// TODO
	return nextNode;
}

std::shared_ptr<CFGNode> SimpleControlFlow::generateFromWhile(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode) {
	int lineNumber = statementNode->getLineNumber();
	std::shared_ptr<CFGNode> node = std::make_shared<CFGNode>(lineNumber);
	node->addChild(nextNode);

	std::shared_ptr<ASTNode> statementListNode = this->getStatementList(statementNode, WHILE_STATEMENT_LIST_INDEX);
	std::shared_ptr<CFGNode> whileLoopNode = this->generateFromStatementList(statementListNode, node);
	node->addChild(whileLoopNode);

	return node;
}