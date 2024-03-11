#include "StatementWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
StatementWriter::StatementWriter(std::shared_ptr<StatementStore> as) : statementStore(std::move(as)) {}

bool StatementWriter::addEntity(int entity) {
	return insertStatement(entity);
}

void StatementWriter::clear() {
	statementStore->clear();
}

bool StatementWriter::insertStatement(int stmtNum) {
	return statementStore->addEntity(stmtNum);
}
// ai-gen end
