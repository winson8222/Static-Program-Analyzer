#include "sp/DesignExtractor/Visitor/AssignVisitor.h"

AssignVisitor::AssignVisitor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
	: StatementVisitor(root, pkbWriterManager) {
	if (root->type != ASTNodeType::ASSIGN) {
		throw std::invalid_argument("ERROR: AssignVisitor - not an assign node");
	}
}

void AssignVisitor::visit() {
	// TODO
	AssignExtractor assignExtractor(this->root, this->pkbWriterManager);
	assignExtractor.extract();

	
}