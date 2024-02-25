#include "sp/DesignExtractor/Visitor/WhileVisitor.h"

WhileVisitor::WhileVisitor(std::shared_ptr<ASTNode> root, 
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (root->type != ASTNodeType::WHILE) {
		throw std::runtime_error("ERROR: Cannot initialized a non-WHILE node");
	}

	if (root->children.size() != 2) {
		throw std::runtime_error("ERROR: While node is not correct");
	}

	this->contexts = listnode(context.begin(), context.end());
}

void WhileVisitor::visit() {
	// do nothing
	std::shared_ptr<ASTNode> expression = root->children[0];
	std::shared_ptr<ASTNode> statementList = root->children[1];

	WhileExtractor whileExtractor(root, pkbWriterManager);
	whileExtractor.extract();

	ExpressionVisitor expressionVisitor(expression, pkbWriterManager);
	expressionVisitor.setUsedContext(contexts, root);
	expressionVisitor.visit();

	StatementListVisitor statementListVisitor(statementList, pkbWriterManager);
	statementListVisitor.setContext(contexts, root);
	statementListVisitor.visit();

	setParents(this->contexts, this->root, this->pkbWriterManager);
}

void WhileVisitor::setParents(listnode contexts, std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager) {
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

void WhileVisitor::addContext(std::shared_ptr<ASTNode> context) {
	
}