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
	// do nothing
	handleWhileExtraction(this->root);
	handleExpressionVisitor();
	handleStatementListVisitor(this->statementList);
	setParents(this->contexts, this->root, this->pkbWriterManager);
}

void WhileVisitor::handleWhileExtraction(std::shared_ptr<ASTNode> root) {
	WhileExtractor whileExtractor(root, pkbWriterManager->getWhileWriter());
	whileExtractor.extract();
}

void WhileVisitor::handleExpressionVisitor() {
	ExpressionVisitor expressionVisitor(this->expression, pkbWriterManager);
	expressionVisitor.setUsedContext(contexts, root);
	expressionVisitor.visit();
	// expressionVisitor.handlePatternExtraction(this->expression, ASTNodeType::WHILE);
}

void WhileVisitor::handleStatementListVisitor(std::shared_ptr<ASTNode> statementList) {
	StatementListVisitor statementListVisitor(statementList, pkbWriterManager);
	statementListVisitor.setContext(contexts, root);
	statementListVisitor.visit();
}