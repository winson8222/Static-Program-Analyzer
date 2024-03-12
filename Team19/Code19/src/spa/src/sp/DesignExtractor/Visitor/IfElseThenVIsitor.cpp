#include "sp/DesignExtractor/Visitor/IfElseThenVisitor.h"

IfElseThenVisitor::IfElseThenVisitor(std::shared_ptr<ASTNode> root, 
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (root->type != ASTNodeType::IF_ELSE_THEN) {
		throw std::invalid_argument("ERROR: IfElseThenVisitor - input root is not of type ASTNodeType::IF_ELSE_THEN");
	}

	if (root->children.size() != IF_ELSE_THEN_NUM_CHILDREN){
		throw std::invalid_argument("ERROR: IfElseThenVisitor - input root does not have 3 children");
	}

	this->contexts = listnode(context.begin(), context.end());
	this->condition = root->children[IF_EXPR_INDEX];
	this->thenStatementList = root->children[THEN_STMT_INDEX];
	this->elseStatementList = root->children[ELSE_STMT_INDEX];
}


void IfElseThenVisitor::visit() {
	handleIfExtractor(this->root);
	handleExpressionVisitor(this->condition);
	handleStatementListVisitor(this->thenStatementList);
	handleStatementListVisitor(this->elseStatementList);
	setParents(this->contexts, this->root, this->pkbWriterManager);
}

void IfElseThenVisitor::handleIfExtractor(std::shared_ptr<ASTNode> root) {
	IfThenElseExtractor ifThenElseExtractor(root, pkbWriterManager->getIfWriter());
	ifThenElseExtractor.extract();
}

void IfElseThenVisitor::handleExpressionVisitor(std::shared_ptr<ASTNode> condition) {
	ExpressionVisitor expressionVisitor(condition, pkbWriterManager);
	expressionVisitor.setUsedContext(contexts, root);
	expressionVisitor.visit();
	// expressionVisitor.handlePatternExtraction(condition, ASTNodeType::IF_ELSE_THEN);
}

void IfElseThenVisitor::handleStatementListVisitor(std::shared_ptr<ASTNode> statementList) {
	StatementListVisitor statementListVisitor(statementList, pkbWriterManager);
	statementListVisitor.setContext(contexts, root);
	statementListVisitor.visit();
}