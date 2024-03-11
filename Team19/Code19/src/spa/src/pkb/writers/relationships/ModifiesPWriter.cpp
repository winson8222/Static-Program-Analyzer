#include "ModifiesPWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
ModifiesPWriter::ModifiesPWriter(std::shared_ptr<ModifiesPStore> store) : modifiesPStore(std::move(store)) {}

void ModifiesPWriter::addModifiesP(std::string proc, std::string var) {
	modifiesPStore->addRelationship(proc, var);
}

void ModifiesPWriter::addRelationship(std::string proc, std::string var) {
	addModifiesP(proc, var);
}

void ModifiesPWriter::clear() {
	modifiesPStore->clear();
}
