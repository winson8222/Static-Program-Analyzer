#include "CallProcNameReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
CallProcNameReader::CallProcNameReader(std::shared_ptr<CallProcNameStore> store) : callProcNameStore(std::move(store)) {}

// Custom methods
std::unordered_set<int> CallProcNameReader::getCallers(std::string procName) const {
    return callProcNameStore->getLinker(procName);
}

std::unordered_set<std::string> CallProcNameReader::getCalledProcedureName(int statementNumber) const {
    return std::unordered_set<std::string>({callProcNameStore->getLinked(statementNumber)});
}

bool CallProcNameReader::isCalled(int statementNumber, std::string procName) const {
    return callProcNameStore->hasLink(statementNumber, procName);
}

// Inherited methods
bool CallProcNameReader::isEmpty() const {
    return callProcNameStore->isEmpty();
}

bool CallProcNameReader::hasLink(int statementNumber, std::string procName) const {
    return callProcNameStore->hasLink(statementNumber, procName);
}

std::unordered_set<int> CallProcNameReader::getLinker(std::string procName) const {
    return callProcNameStore->getLinker(procName);
}

std::string CallProcNameReader::getLinked(int statementNumber) const {
    return callProcNameStore->getLinked(statementNumber);
}
// ai-gen end
