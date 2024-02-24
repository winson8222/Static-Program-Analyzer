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
	// TODO
	IfThenElseExtractor ifThenElseExtractor(root, pkbWriterManager);
	ifThenElseExtractor.extract();

	std::shared_ptr<ASTNode> condition = root->children[0];
	std::shared_ptr<ASTNode> thenStatementList = root->children[1];
	std::shared_ptr<ASTNode> elseStatementList = root->children[2];

	ExpressionVisitor expressionVisitor(condition, pkbWriterManager);
	expressionVisitor.visit();

	StatementListVisitor thenStatementListVisitor(thenStatementList, pkbWriterManager);
	thenStatementListVisitor.setContext(contexts, root);
	thenStatementListVisitor.visit();

	StatementListVisitor elseStatementListVisitor(elseStatementList, pkbWriterManager);
	elseStatementListVisitor.setContext(contexts, root);
	elseStatementListVisitor.visit();

	int size = contexts.size();
	for (int i = 0; i < size; i++) {
		std::shared_ptr<ASTNode> context = contexts[i];
		if (context->type == ASTNodeType::PROCEDURE) continue;
		ParentTExtractor parentExtractor(context, root, pkbWriterManager);
		parentExtractor.extract();
	}
    if (size > 0 && contexts[size - 1]->type != ASTNodeType::PROCEDURE) {
		ParentExtractor parentExtractor(contexts[size - 1], root, pkbWriterManager);
		parentExtractor.extract();
	}
}

void IfElseThenVisitor::addContext(std::shared_ptr<ASTNode> context) {
	// Do nothing
}