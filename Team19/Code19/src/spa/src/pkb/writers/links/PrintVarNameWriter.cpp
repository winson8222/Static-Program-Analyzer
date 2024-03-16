#include "pkb/writers/links/PrintVarNameWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
PrintVarNameWriter::PrintVarNameWriter(std::shared_ptr<PrintVarNameStore> store) : printVarNameStore(std::move(store)) {}

void PrintVarNameWriter::addPrintVarName(int statementNumber, std::string varName) {
    printVarNameStore->addLink(statementNumber, varName);
}

void PrintVarNameWriter::addLink(int statementNumber, std::string varName) {
    addPrintVarName(statementNumber, varName);
}

void PrintVarNameWriter::clear() {
    printVarNameStore->clear();
}
// ai-gen end
