#include "sp/DesignExtractor/Extractor/IfElseThenExtractor.h"

void IfThenElseExtractor::extract() {
	// Extract if then else and insert into PKB
	this->pkbWriterManager->getIfWriter()->insertIf(this->root->lineNumber);

	// Put statements to PKB
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}