#include "WhileWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
WhileWriter::WhileWriter(std::shared_ptr<WhileStore> as) : whileStore(std::move(as)) {}

bool WhileWriter::addEntity(int entity) {
	return insertWhile(entity);
}

void WhileWriter::clear() {
	whileStore->clear();
}

bool WhileWriter::insertWhile(int stmtNum) {
	return whileStore->addEntity(stmtNum);
}
// ai-gen end
