#include "PrintVarNameReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
PrintVarNameReader::PrintVarNameReader(std::shared_ptr<PrintVarNameStore> store) : printVarNameStore(std::move(store)) {}

// Custom methods
std::unordered_set<int> PrintVarNameReader::getPrints(std::string varName) {
    return printVarNameStore->getLinker(varName);
}

std::string PrintVarNameReader::getPrintVariableName(int statementNumber) {
    return printVarNameStore->getLinked(statementNumber);
}

bool PrintVarNameReader::isPrinted(int statementNumber, std::string varName) {
    return printVarNameStore->hasLink(statementNumber, varName);
}

std::unordered_set<std::string> PrintVarNameReader::getAllPrintVariables() {
    return printVarNameStore->getAllLinked();
}

// Inherited methods
bool PrintVarNameReader::isEmpty() {
    return printVarNameStore->isEmpty();
}

bool PrintVarNameReader::hasLink(int statementNumber, std::string varName) {
    return printVarNameStore->hasLink(statementNumber, varName);
}

std::unordered_set<int> PrintVarNameReader::getLinker(std::string varName) {
    return printVarNameStore->getLinker(varName);
}

std::string PrintVarNameReader::getLinked(int statementNumber) {
    return printVarNameStore->getLinked(statementNumber);
}

std::unordered_set<std::string> PrintVarNameReader::getAllLinked() {
    return printVarNameStore->getAllLinked();
}
// ai-gen end
