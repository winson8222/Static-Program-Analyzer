#include "sp/DesignExtractor/Visitor/IfElseThenVisitor.h"

IfElseThenVisitor::IfElseThenVisitor(std::shared_ptr<ASTNode> root, 
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (!root->equalType(ASTNodeType::IF_ELSE_THEN)) {
		throw std::invalid_argument("ERROR: IfElseThenVisitor - input root is not of type ASTNodeType::IF_ELSE_THEN");
	}

	auto children = root->getChildren();
	if (children.size() != IF_ELSE_THEN_NUM_CHILDREN){
		throw std::invalid_argument("ERROR: IfElseThenVisitor - input root does not have 3 children");
	}

	this->contexts = listnode(context.begin(), context.end());
	this->condition = children[IF_EXPR_INDEX];
	this->thenStatementList = children[THEN_STMT_INDEX];
	this->elseStatementList = children[ELSE_STMT_INDEX];
}


void IfElseThenVisitor::visit() {
	handleIfExtractor();
	handleExpressionVisitor();
	handleStatementListVisitor(this->thenStatementList);
	handleStatementListVisitor(this->elseStatementList);
	setParents(this->contexts, this->root, this->pkbWriterManager);
}

void IfElseThenVisitor::handleIfExtractor() {
	IfThenElseExtractor ifThenElseExtractor(root, pkbWriterManager->getIfWriter());
	ifThenElseExtractor.extract();
}

void IfElseThenVisitor::handleExpressionVisitor() {
	ExpressionVisitor expressionVisitor(condition, ASTNodeType::IF_ELSE_THEN, pkbWriterManager);
	expressionVisitor.setUsedContext(contexts, root);
	expressionVisitor.visit();
}

void IfElseThenVisitor::handleStatementListVisitor(std::shared_ptr<ASTNode> statementList) {
	StatementListVisitor statementListVisitor(statementList, pkbWriterManager);
	statementListVisitor.setContext(contexts, root);
	statementListVisitor.visit();
}