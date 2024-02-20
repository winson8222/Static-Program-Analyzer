#include "sp/DesignExtractor/Extractor/AssignExtractor.h"

void AssignExtractor::extract() {
	// Extract all the assign statements
	this->pkbWriterManager->getAssignWriter()->insertAssign(this->root->lineNumber);
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}