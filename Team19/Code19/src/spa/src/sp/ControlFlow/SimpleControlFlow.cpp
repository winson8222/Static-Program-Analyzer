#include "SimpleControlFlow.h"
#include <stdexcept>

SimpleControlFlow::SimpleControlFlow(std::shared_ptr<ASTNode> root) : root(root) {
	if (!root->equalType(ASTNodeType::PROGRAMS)) {
		throw std::runtime_error("Node type cannot be non-program");
	}
}

std::shared_ptr<std::vector<std::shared_ptr<CFGNode>>> SimpleControlFlow::createControlFlowGraphs() {
	std::vector<std::shared_ptr<ASTNode>> procedures = this->root->getChildren();

	std::shared_ptr<std::vector<std::shared_ptr<CFGNode>>> controlFlowGraphs = std::make_shared<std::vector<std::shared_ptr<CFGNode>>>();

	for (auto& procedure : procedures) {
		std::shared_ptr<CFGNode> procedureCfg = this->generateFromProcedure(procedure);
		controlFlowGraphs->push_back(procedureCfg);
	}

	return controlFlowGraphs;
};

std::shared_ptr<ASTNode> SimpleControlFlow::getStatementList(std::shared_ptr<ASTNode> node, int index) {
	return node->getChildByIndex(index);
};

std::shared_ptr<CFGNode> SimpleControlFlow::generateFromProcedure(std::shared_ptr<ASTNode> procedureNode) {
	std::shared_ptr<ASTNode> statementListNode = this->getStatementList(procedureNode, PROCEDURE_STATEMENT_LIST_INDEX);
	std::shared_ptr<CFGNode> endOfProcedureDummyNode = CFGNode::getDummyNode();
	return this->generateFromStatementList(statementListNode, endOfProcedureDummyNode);
}

std::shared_ptr<CFGNode> SimpleControlFlow::generateFromStatementList(std::shared_ptr<ASTNode> statementListNode, std::shared_ptr<CFGNode> nextNode) {
	std::vector<std::shared_ptr<ASTNode>> statements = statementListNode->getChildren();

	// Recursively add the node representing the next line as a child of the current node.
	for (int i = statements.size() - 1; i >= 0; i--) {
		std::shared_ptr<CFGNode> node = this->generateFromStatement(statements[i], nextNode);
		nextNode = node;
	}

	return nextNode;
}

std::shared_ptr<CFGNode> SimpleControlFlow::generateFromStatement(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode) {
	if (statementNode->equalType(ASTNodeType::IF_ELSE_THEN)) {
		return this->generateFromIfElseThen(statementNode, nextNode);
	}
	else if (statementNode->equalType(ASTNodeType::WHILE)) {
		return this->generateFromWhile(statementNode, nextNode);
	}

	int lineNumber = statementNode->getLineNumber();
	std::shared_ptr<CFGNode> node = std::make_shared<CFGNode>(lineNumber);
	node->addChild(nextNode);

	return node;
}

std::shared_ptr<CFGNode> SimpleControlFlow::generateFromIfElseThen(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode) {
	int lineNumber = statementNode->getLineNumber();
	std::shared_ptr<CFGNode> node = std::make_shared<CFGNode>(lineNumber);

	std::shared_ptr<ASTNode> ifNode = this->getStatementList(statementNode, IF_STATEMENT_LIST_INDEX);
	std::shared_ptr<CFGNode> ifBlockNode = this->generateFromStatementList(ifNode, nextNode);
	node->addChild(ifBlockNode);

	std::shared_ptr<ASTNode> elseNode = this->getStatementList(statementNode, ELSE_STATEMENT_LIST_INDEX);
	std::shared_ptr<CFGNode> elseBlockNode = this->generateFromStatementList(elseNode, nextNode);
	node->addChild(elseBlockNode);

	return node;
}

std::shared_ptr<CFGNode> SimpleControlFlow::generateFromWhile(std::shared_ptr<ASTNode> statementNode, std::shared_ptr<CFGNode> nextNode) {
	int lineNumber = statementNode->getLineNumber();
	std::shared_ptr<CFGNode> node = std::make_shared<CFGNode>(lineNumber);

	std::shared_ptr<ASTNode> statementListNode = this->getStatementList(statementNode, WHILE_STATEMENT_LIST_INDEX);
	std::shared_ptr<CFGNode> whileBlockNode = this->generateFromStatementList(statementListNode, node);
	node->addChild(whileBlockNode);
	node->addChild(nextNode);

	return node;
}
