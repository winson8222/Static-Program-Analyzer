#include "CallWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
CallWriter::CallWriter(std::shared_ptr<CallStore> as) : callStore(std::move(as)) {}

bool CallWriter::addEntity(int entity) {
	return insertCall(entity);
}

void CallWriter::clear() {
	callStore->clear();
}

bool CallWriter::insertCall(int stmtNum) {
	return callStore->addEntity(stmtNum);
}
// ai-gen end
