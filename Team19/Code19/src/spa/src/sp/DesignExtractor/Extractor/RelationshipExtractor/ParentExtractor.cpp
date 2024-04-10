#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ParentExtractor.h"

ParentExtractor::ParentExtractor(std::shared_ptr<ParentWriter> parentWriter)
	: IRelationshipExtractor() {
	this->parentWriter = parentWriter;
}

void ParentExtractor::extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	// Extract all the parent relationships
	this->parentWriter->addParent(
		ast1->getLineNumber(), ast2->getLineNumber()
	);
}

ParentTExtractor::ParentTExtractor(std::shared_ptr<ParentTWriter> parentTWriter)
	: IRelationshipExtractor() {
	this->parentTWriter = parentTWriter;
}


void ParentTExtractor::extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	// Extract all the parent relationships
	this->parentTWriter->addParentT(
		ast1->getLineNumber(), ast2->getLineNumber()
	);
}
