#include "IfWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
IfWriter::IfWriter(std::shared_ptr<IfStore> as) : ifStore(std::move(as)) {}

bool IfWriter::addEntity(int entity) {
	return insertIf(entity);
}

void IfWriter::clear() {
	ifStore->clear();
}

bool IfWriter::insertIf(int stmtNum) {
	return ifStore->addEntity(stmtNum);
}
// ai-gen end
