#include "sp/DesignExtractor/Visitor/IfElseThenVisitor.h"

IfElseThenVisitor::IfElseThenVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, pkbWriterManager) {
	if (root->type != ASTNodeType::IF_ELSE_THEN) {
		throw std::invalid_argument("ERROR: IfElseThenVisitor - input root is not of type ASTNodeType::IF_ELSE_THEN");
	}

	if (root->children.size() != 3) {
		throw std::invalid_argument("ERROR: IfElseThenVisitor - input root does not have 3 children");
	}
}

void IfElseThenVisitor::visit() {
	// TODO
	IfThenElseExtractor ifThenElseExtractor(root, pkbWriterManager);
	ifThenElseExtractor.extract();

	std::shared_ptr<ASTNode> condition = root->children[0];
	std::shared_ptr<ASTNode> thenStatementList = root->children[1];
	std::shared_ptr<ASTNode> elseStatementList = root->children[2];

	RelExpressionVisitor expressionVisitor(condition, pkbWriterManager);
	expressionVisitor.visit();

	StatementListVisitor thenStatementListVisitor(thenStatementList, pkbWriterManager);
	thenStatementListVisitor.visit();

	StatementListVisitor elseStatementListVisitor(elseStatementList, pkbWriterManager);
	elseStatementListVisitor.visit();
}