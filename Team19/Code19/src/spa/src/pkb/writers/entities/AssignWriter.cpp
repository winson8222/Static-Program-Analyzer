#include "AssignWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
AssignWriter::AssignWriter(std::shared_ptr<AssignStore> as) : assignStore(std::move(as)) {}

bool AssignWriter::addEntity(int entity) {
	return insertAssign(entity);
}

void AssignWriter::clear() {
	assignStore->clear();
}

bool AssignWriter::insertAssign(int stmtNum) {
	return assignStore->addEntity(stmtNum);
}
// ai-gen end
