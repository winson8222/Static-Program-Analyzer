#include "sp/DesignExtractor/Extractor/ReadExtractor.h"

void ReadExtractor::extract() {
	// Insert read into PKB
	this->pkbWriterManager->getReadWriter()->insertRead(this->root->lineNumber);

	// Insert statement into PKB
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}