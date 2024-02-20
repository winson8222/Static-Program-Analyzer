#include "sp/DesignExtractor/Visitor/WhileVisitor.h"

WhileVisitor::WhileVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, pkbWriterManager) {
	if (root->type != ASTNodeType::WHILE) {
		throw std::runtime_error("ERROR: Cannot initialized a non-WHILE node");
	}

	if (root->children.size() != 2) {
		throw std::runtime_error("ERROR: While node is not correct");
	}
}

void WhileVisitor::visit() {
	// do nothing
	std::shared_ptr<ASTNode> expression = root->children[0];
	std::shared_ptr<ASTNode> statementList = root->children[1];

	WhileExtractor whileExtractor(root, pkbWriterManager);
	whileExtractor.extract();

	RelExpressionVisitor expressionVisitor(expression, pkbWriterManager);
	expressionVisitor.visit();

	StatementListVisitor statementListVisitor(statementList, pkbWriterManager);
	statementListVisitor.visit();
}