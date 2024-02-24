#include "sp/DesignExtractor/Extractor/PrintExtractor.h"

void PrintExtractor::extract() {
	// Insert print statement into PKB
	this->pkbWriterManager->getPrintWriter()->insertPrint(this->root->lineNumber);

	// Insert statement into PKB
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}