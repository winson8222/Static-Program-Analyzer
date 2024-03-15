#include "ReadVarNameReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
ReadVarNameReader::ReadVarNameReader(std::shared_ptr<ReadVarNameStore> store) : readVarNameStore(std::move(store)) {}

// Custom methods
std::unordered_set<int> ReadVarNameReader::getReaders(std::string varName) {
    return readVarNameStore->getLinker(varName);
}

std::unordered_set<std::string> ReadVarNameReader::getReadVariableName(int statementNumber) {
    return std::unordered_set<std::string>({readVarNameStore->getLinked(statementNumber)});
}

bool ReadVarNameReader::isRead(int statementNumber, std::string varName) {
    return readVarNameStore->hasLink(statementNumber, varName);
}

// Inherited methods
bool ReadVarNameReader::isEmpty() {
    return readVarNameStore->isEmpty();
}

bool ReadVarNameReader::hasLink(int statementNumber, std::string varName) {
    return readVarNameStore->hasLink(statementNumber, varName);
}

std::unordered_set<int> ReadVarNameReader::getLinker(std::string varName) {
    return readVarNameStore->getLinker(varName);
}

std::string ReadVarNameReader::getLinked(int statementNumber) {
    return readVarNameStore->getLinked(statementNumber);
}
// ai-gen end
