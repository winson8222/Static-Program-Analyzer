#include "FollowsWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
FollowsWriter::FollowsWriter(std::shared_ptr<FollowsStore> store) : followsStore(std::move(store)) {}

void FollowsWriter::addFollows(int stmt1, int stmt2) {
	followsStore->addRelationship(stmt1, stmt2);
}

void FollowsWriter::addRelationship(int stmt1, int stmt2) {
	addFollows(stmt1, stmt2);
}

void FollowsWriter::clear() {
	followsStore->clear();
}
// ai-gen end
