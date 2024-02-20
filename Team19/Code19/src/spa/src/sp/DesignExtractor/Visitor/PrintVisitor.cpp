#include "sp/DesignExtractor/Visitor/PrintVisitor.h"

PrintVisitor::PrintVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: IVisitor(root, pkbWriterManager) {
	if (root->type != ASTNodeType::PRINT) {
		throw std::invalid_argument("PrintVisitor - root is not of type PRINT");
	}
	if (root->children.size() != 1) {
		throw std::invalid_argument("PrintVisitor - root does not have 1 child");
	}
}

void PrintVisitor::visit(std::shared_ptr<ASTNode> node) {
	// do nothing for now
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
}