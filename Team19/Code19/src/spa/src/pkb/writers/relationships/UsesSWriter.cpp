#include "UsesSWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
UsesSWriter::UsesSWriter(std::shared_ptr<UsesSStore> store) : usesSStore(std::move(store)) {}

void UsesSWriter::addRelationship(int stmtNum, std::string var) {
	addUsesS(stmtNum, var);
}

void UsesSWriter::clear() {
  usesSStore->clear();
}

void UsesSWriter::addUsesS(int stmtNum, const std::string& var) {
  usesSStore->addRelationship(stmtNum, var);
}
// ai-gen end
