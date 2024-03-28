#include "sp/DesignExtractor/Extractor/EntityExtractor/AssignExtractor.h"

AssignExtractor::AssignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<AssignWriter> assignWriter)
	: IEntityExtractor(root) {
	if (!root->equalType(ASTNodeType::ASSIGN)) {
		throw std::runtime_error("ERROR: AssignExtractor root node type not supported");
	}
	this->assignWriter = assignWriter;
}

void AssignExtractor::extract() {
	// Extract all the assign statements
	this->assignWriter->insertAssign(this->root->getLineNumber());
}
