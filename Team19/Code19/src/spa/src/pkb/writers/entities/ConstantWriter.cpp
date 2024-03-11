#include "ConstantWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
ConstantWriter::ConstantWriter(std::shared_ptr<ConstantStore> as) : constantStore(std::move(as)) {}

bool ConstantWriter::addEntity(int entity) {
	return insertConstant(entity);
}

void ConstantWriter::clear() {
	constantStore->clear();
}

bool ConstantWriter::insertConstant(int stmtNum) {
	return constantStore->addEntity(stmtNum);
}
// ai-gen end
