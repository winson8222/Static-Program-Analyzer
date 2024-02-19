#include "sp/DesignExtractor/Extractor/ProcedureExtractor.h"

void ProcedureExtractor::extract() {
	this->pkbWriterManager->getProcedureWriter()->insertProcedure(root->value);
}