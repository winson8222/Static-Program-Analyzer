#include "ParentWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
ParentWriter::ParentWriter(std::shared_ptr<ParentStore> store) : parentStore(std::move(store)) {}

void ParentWriter::addParent(int stmt1, int stmt2) {
	parentStore->addRelationship(stmt1, stmt2);
}

void ParentWriter::addRelationship(int stmt1, int stmt2) {
	addParent(stmt1, stmt2);
}

void ParentWriter::clear() {
	parentStore->clear();
}
// ai-gen end
