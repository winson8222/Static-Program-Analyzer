#include "sp/DesignExtractor/Extractor/IfElseThenExtractor.h"

void IfThenElseExtractor::extract() {
	this->pkbWriterManager->getIfWriter()->insertIf(this->root->lineNumber);
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}