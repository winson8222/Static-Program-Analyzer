#include "sp/DesignExtractor/Extractor/WhileExtractor.h"

void WhileExtractor::extract() {
	this->pkbWriterManager->getWhileWriter()->insertWhile(this->root->lineNumber);
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}