#include "sp/DesignExtractor/Extractor/VariableExtractor.h"

void VariableExtractor::extract() {
	this->pkbWriterManager->getVariableWriter()->addEntity(this->root->value);
}