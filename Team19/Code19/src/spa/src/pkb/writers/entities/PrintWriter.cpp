#include "PrintWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
PrintWriter::PrintWriter(std::shared_ptr<PrintStore> as) : printStore(std::move(as)) {}

bool PrintWriter::addEntity(int entity) {
	return insertPrint(entity);
}

void PrintWriter::clear() {
	printStore->clear();
}

bool PrintWriter::insertPrint(int stmtNum) {
	return printStore->addEntity(stmtNum);
}
// ai-gen end
