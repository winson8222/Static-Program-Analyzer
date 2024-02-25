#include "sp/DesignExtractor/Extractor/WhileExtractor.h"

void WhileExtractor::extract() {
	// Insert while entity into pkb
	this->pkbWriterManager->getWhileWriter()->insertWhile(this->root->lineNumber);

	// Insert while as a statement into pkb
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}