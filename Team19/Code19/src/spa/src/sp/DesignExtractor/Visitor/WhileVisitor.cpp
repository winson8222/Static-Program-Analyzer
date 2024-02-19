#include "sp/DesignExtractor/Visitor/WhileVisitor.h"

WhileVisitor::WhileVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	if (root->type != ASTNodeType::WHILE) {
		throw std::runtime_error("ERROR: Cannot initialized a non-WHILE node");
	}
}

void WhileVisitor::visit(std::shared_ptr<ASTNode> node) {
	// do nothing
}

void WhileVisitor::visit() {
	// do nothing
	if (root->children.size() != 2) {
		throw std::runtime_error("ERROR: While node is not correct");
	}
	auto statementList = root->children[0];
	StatementListVisitor statementListVisitor(statementList, pkbWriterManager);
	statementListVisitor.visit();
}