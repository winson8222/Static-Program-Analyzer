#include "sp/DesignExtractor/Extractor/CallExtractor.h"

void CallExtractor::extract() {
	// Extract all the call
	this->pkbWriterManager->getCallWriter()->insertCall(this->root->lineNumber);
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}