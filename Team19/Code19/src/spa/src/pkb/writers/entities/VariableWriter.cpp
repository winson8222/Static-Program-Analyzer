#include "VariableWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
VariableWriter::VariableWriter(std::shared_ptr<VariableStore> as) : variableStore(std::move(as)) {}

bool VariableWriter::addEntity(std::string entity) {
	return insertVariable(entity);
}

void VariableWriter::clear() {
	variableStore->clear();
}

bool VariableWriter::insertVariable(std::string stmtNum) {
	return variableStore->addEntity(stmtNum);
}
// ai-gen end
