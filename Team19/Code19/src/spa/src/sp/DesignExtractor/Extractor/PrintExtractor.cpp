#include "sp/DesignExtractor/Extractor/PrintExtractor.h"

void PrintExtractor::extract() {
	this->pkbWriterManager->getPrintWriter()->insertPrint(this->root->lineNumber);
	this->pkbWriterManager->getStatementWriter()->insertStatement(this->root->lineNumber);
}