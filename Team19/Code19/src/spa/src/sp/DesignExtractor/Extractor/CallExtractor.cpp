#include "sp/DesignExtractor/Extractor/CallExtractor.h"

void CallExtractor::extract() {
	// Extract all the call statements
	this->pkbWriterManager->getCallWriter()->insertCall(this->root->lineNumber);

	// Extract all the statements
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}