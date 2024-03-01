#include "ModifiesSWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
ModifiesSWriter::ModifiesSWriter(std::shared_ptr<ModifiesSStore> store) : modifiesSStore(std::move(store)) {}

void ModifiesSWriter::addModifiesS(int stmt, std::string var) {
	modifiesSStore->addRelationship(stmt, var);
}

void ModifiesSWriter::addRelationship(int stmt, std::string var) {
	addModifiesS(stmt, var);
}

void ModifiesSWriter::clear() {
	modifiesSStore->clear();
}
// ai-gen end
