#include "NextWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
NextWriter::NextWriter(std::shared_ptr<NextStore> store) : nextStore(std::move(store)) {}

void NextWriter::addNext(int stmt1, int stmt2) {
	nextStore->addRelationship(stmt1, stmt2);
}

void NextWriter::addRelationship(int stmt1, int stmt2) {
	addNext(stmt1, stmt2);
}

void NextWriter::clear() {
	nextStore->clear();
}
// ai-gen end
