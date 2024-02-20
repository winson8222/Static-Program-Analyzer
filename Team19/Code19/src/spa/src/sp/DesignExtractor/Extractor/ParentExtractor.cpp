#include "sp/DesignExtractor/Extractor/ParentExtractor.h"

void ParentExtractor::extract() {
	// Extract all the parent relationships
	this->pkbWriterManager->getParentWriter()->addParent(
		this->ast1->lineNumber, this->ast2->lineNumber
	);
}