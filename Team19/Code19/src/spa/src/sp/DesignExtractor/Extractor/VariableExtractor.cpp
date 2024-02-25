#include "sp/DesignExtractor/Extractor/VariableExtractor.h"

void VariableExtractor::extract() {
	// Extract all variables to the PKB
	this->pkbWriterManager->getVariableWriter()->addEntity(this->root->value);
}