#include "ReadWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
ReadWriter::ReadWriter(std::shared_ptr<ReadStore> as) : readStore(std::move(as)) {}

bool ReadWriter::addEntity(int entity) {
	return insertRead(entity);
}

void ReadWriter::clear() {
	readStore->clear();
}

bool ReadWriter::insertRead(int stmtNum) {
	return readStore->addEntity(stmtNum);
}
// ai-gen end
