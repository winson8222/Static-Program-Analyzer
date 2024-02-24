#include "sp/DesignExtractor/Extractor/ProcedureExtractor.h"

void ProcedureExtractor::extract() {
	// Insert procedures into PKB
	this->pkbWriterManager->getProcedureWriter()->insertProcedure(root->value);
}