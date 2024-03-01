#include "FollowsTWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
FollowsTWriter::FollowsTWriter(std::shared_ptr<FollowsTStore> store) : followsTStore(std::move(store)) {}

void FollowsTWriter::addFollowsT(int stmt1, int stmt2) {
	followsTStore->addRelationship(stmt1, stmt2);
}

void FollowsTWriter::addRelationship(int stmt1, int stmt2) {
	addFollowsT(stmt1, stmt2);
}

void FollowsTWriter::clear() {
	followsTStore->clear();
}
// ai-gen end
