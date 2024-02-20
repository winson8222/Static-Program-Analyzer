#include "sp/DesignExtractor/Visitor/PrintVisitor.h"

PrintVisitor::PrintVisitor(std::shared_ptr<ASTNode> root, 
	listnode context,
	std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, context, pkbWriterManager) {
	if (root->type != ASTNodeType::PRINT) {
		throw std::invalid_argument("PrintVisitor - root is not of type PRINT");
	}
	if (root->children.size() != 1) {
		throw std::invalid_argument("PrintVisitor - root does not have 1 child");
	}
	this->contexts = listnode(context.begin(), context.end());
}


void PrintVisitor::visit() {
	// TODO
	if (this->root->type != ASTNodeType::PRINT) {
		throw std::runtime_error("This is not a print node!");
	}
	// I'm here in the Print Visitor - now my purpose is
	// to populate print statements and the variable (and the uses relationships)

	PrintExtractor printExtractor(this->root, this->pkbWriterManager);
	printExtractor.extract();

	VariableExtractor variableExtractor(this->root->children[0], this->pkbWriterManager);
	variableExtractor.extract();

	int size = contexts.size();
	for (int i = 0; i < size; i++) {
		std::shared_ptr<ASTNode> context = contexts[i];
		if (context->type == ASTNodeType::PROCEDURE) continue;
		ParentTExtractor parentExtractor(context, root, pkbWriterManager);
		parentExtractor.extract();
	}
	if (size > 0) {
		ParentExtractor parentExtractor(contexts[size - 1], root, pkbWriterManager);
		parentExtractor.extract();
	}
}

void PrintVisitor::addContext(std::shared_ptr<ASTNode> context) {
	// do nothing
}