#include "CallProcNameReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
CallProcNameReader::CallProcNameReader(std::shared_ptr<CallProcNameStore> store) : callProcNameStore(std::move(store)) {}

// Custom methods
std::unordered_set<int> CallProcNameReader::getCallers(std::string procName) {
    return callProcNameStore->getLinker(procName);
}

std::string CallProcNameReader::getCalledProcedureName(int statementNumber) {
    return callProcNameStore->getLinked(statementNumber);
}

bool CallProcNameReader::isCalled(int statementNumber, std::string procName) {
    return callProcNameStore->hasLink(statementNumber, procName);
}

std::unordered_set<std::string> CallProcNameReader::getAllCalledProcedures() {
    return callProcNameStore->getAllLinked();
}

// Inherited methods
bool CallProcNameReader::isEmpty() {
    return callProcNameStore->isEmpty();
}

bool CallProcNameReader::hasLink(int statementNumber, std::string procName) {
    return callProcNameStore->hasLink(statementNumber, procName);
}

std::unordered_set<int> CallProcNameReader::getLinker(std::string procName) {
    return callProcNameStore->getLinker(procName);
}

std::string CallProcNameReader::getLinked(int statementNumber) {
    return callProcNameStore->getLinked(statementNumber);
}

std::unordered_set<std::string> CallProcNameReader::getAllLinked() {
    return callProcNameStore->getAllLinked();
}
// ai-gen end
