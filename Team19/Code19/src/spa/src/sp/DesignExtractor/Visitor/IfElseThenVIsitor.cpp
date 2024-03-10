#include "sp/DesignExtractor/Visitor/IfElseThenVisitor.h"

IfElseThenVisitor::IfElseThenVisitor(std::shared_ptr<ASTNode> root, 
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (root->type != ASTNodeType::IF_ELSE_THEN) {
		throw std::invalid_argument("ERROR: IfElseThenVisitor - input root is not of type ASTNodeType::IF_ELSE_THEN");
	}

	if (root->children.size() != 3) {
		throw std::invalid_argument("ERROR: IfElseThenVisitor - input root does not have 3 children");
	}

	this->contexts = listnode(context.begin(), context.end());
}


void IfElseThenVisitor::visit() {
	// Extract if-then-else
	IfThenElseExtractor ifThenElseExtractor(root, pkbWriterManager);
	ifThenElseExtractor.extract();

	std::shared_ptr<ASTNode> condition = root->children[0];
	std::shared_ptr<ASTNode> thenStatementList = root->children[1];
	std::shared_ptr<ASTNode> elseStatementList = root->children[2];

	// Visit all expressions
	ExpressionVisitor expressionVisitor(condition, pkbWriterManager);
	expressionVisitor.setUsedContext(contexts, root);
	expressionVisitor.visit();

	StatementListVisitor thenStatementListVisitor(thenStatementList, pkbWriterManager);
	thenStatementListVisitor.setContext(contexts, root);
	thenStatementListVisitor.visit();

	StatementListVisitor elseStatementListVisitor(elseStatementList, pkbWriterManager);
	elseStatementListVisitor.setContext(contexts, root);
	elseStatementListVisitor.visit();

	setParents(this->contexts, this->root, this->pkbWriterManager);
}