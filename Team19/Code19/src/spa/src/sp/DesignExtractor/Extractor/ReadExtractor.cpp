#include "sp/DesignExtractor/Extractor/ReadExtractor.h"

void ReadExtractor::extract() {
	this->pkbWriterManager->getReadWriter()->insertRead(this->root->lineNumber);
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}