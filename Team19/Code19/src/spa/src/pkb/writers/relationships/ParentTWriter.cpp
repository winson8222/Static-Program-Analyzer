#include "ParentTWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
ParentTWriter::ParentTWriter(std::shared_ptr<ParentTStore> store) : parentTStore(std::move(store)) {}

void ParentTWriter::addParentT(int stmt1, int stmt2) {
	parentTStore->addRelationship(stmt1, stmt2);
}

void ParentTWriter::addRelationship(int stmt1, int stmt2) {
	addParentT(stmt1, stmt2);
}

void ParentTWriter::clear() {
	parentTStore->clear();
}
// ai-gen end
