#include "pkb/writers/links/ReadVarNameWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
ReadVarNameWriter::ReadVarNameWriter(std::shared_ptr<ReadVarNameStore> store) : readVarNameStore(std::move(store)) {}

void ReadVarNameWriter::addReadVarName(int statementNumber, std::string varName) {
    readVarNameStore->addLink(statementNumber, varName);
}

void ReadVarNameWriter::addLink(int statementNumber, std::string varName) {
    addReadVarName(statementNumber, varName);
}

void ReadVarNameWriter::clear() {
    readVarNameStore->clear();
}
// ai-gen end
