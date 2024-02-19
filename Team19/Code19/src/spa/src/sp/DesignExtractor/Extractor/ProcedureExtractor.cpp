#include "sp/DesignExtractor/Extractor/ProcedureExtractor.h"

void ProcedureExtractor::extract() {
	std::cout << "REACHED EXTRACTOR" << std::endl;
	this->pkbWriterManager->getProcedureWriter()->insertProcedure(root->value);
}