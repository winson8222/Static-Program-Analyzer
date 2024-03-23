#include "sp/DesignExtractor/Visitor/WhileVisitor.h"

WhileVisitor::WhileVisitor(std::shared_ptr<ASTNode> root, 
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (!root->equalType(ASTNodeType::WHILE)) {
		throw std::runtime_error("ERROR: Cannot initialized a non-WHILE node");
	}
	this->contexts = listnode(context.begin(), context.end());
	this->expression = root->getChildByIndex(WHILE_EXPRESSION_INDEX);
	this->statementList = root->getChildByIndex(WHILE_STATEMENT_LIST_INDEX);
}

void WhileVisitor::visit() {
	handleWhileExtraction();
	handleExpressionVisitor();
	handleStatementListVisitor();
}

void WhileVisitor::handleWhileExtraction() {
	WhileExtractor whileExtractor(root, pkbWriterManager->getWhileWriter());
	whileExtractor.extract();
}

void WhileVisitor::handleExpressionVisitor() {
	ExpressionVisitor expressionVisitor(this->expression, ASTNodeType::WHILE, pkbWriterManager);
	expressionVisitor.setUsedContext(contexts, root);
	expressionVisitor.visit();
}

void WhileVisitor::handleStatementListVisitor() {
	StatementListVisitor statementListVisitor(statementList, pkbWriterManager);
	statementListVisitor.setContext(contexts, root);
	statementListVisitor.visit();
}