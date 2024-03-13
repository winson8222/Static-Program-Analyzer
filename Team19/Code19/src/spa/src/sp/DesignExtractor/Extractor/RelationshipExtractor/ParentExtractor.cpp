#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ParentExtractor.h"

ParentExtractor::ParentExtractor(std::shared_ptr<ASTNode> ast1,
	std::shared_ptr<ASTNode> ast2,
	std::shared_ptr<ParentWriter> parentWriter)
	: IRelationshipExtractor(ast1, ast2) {
	this->parentWriter = parentWriter;
}

void ParentExtractor::extract() {
	// Extract all the parent relationships
	this->parentWriter->addParent(
		this->ast1->getLineNumber(), this->ast2->getLineNumber()
	);
}

ParentTExtractor::ParentTExtractor(std::shared_ptr<ASTNode> ast1,
	std::shared_ptr<ASTNode> ast2,
	std::shared_ptr<ParentTWriter> parentTWriter)
	: IRelationshipExtractor(ast1, ast2) {
	this->parentTWriter = parentTWriter;
}


void ParentTExtractor::extract() {
	// Extract all the parent relationships
	this->parentTWriter->addParentT(
		this->ast1->getLineNumber(), this->ast2->getLineNumber()
	);
}