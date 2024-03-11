#include "UsesPWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
UsesPWriter::UsesPWriter(std::shared_ptr<UsesPStore> store) : usesPStore(std::move(store)) {}

void UsesPWriter::addUsesP(const std::string& proc, const std::string& var) {
	usesPStore->addRelationship(proc, var);
}

void UsesPWriter::addRelationship(std::string proc, std::string var) {
	addUsesP(proc, var);
}

void UsesPWriter::clear() {
	usesPStore->clear();
}
// ai-gen end
