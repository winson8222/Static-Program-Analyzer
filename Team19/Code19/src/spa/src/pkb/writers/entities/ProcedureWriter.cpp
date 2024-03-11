#include "ProcedureWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
ProcedureWriter::ProcedureWriter(std::shared_ptr<ProcedureStore> as) : procedureStore(std::move(as)) {}

bool ProcedureWriter::addEntity(std::string entity) {
	return insertProcedure(entity);
}

void ProcedureWriter::clear() {
	procedureStore->clear();
}

bool ProcedureWriter::insertProcedure(std::string stmtNum) {
	return procedureStore->addEntity(stmtNum);
}
// ai-gen end
