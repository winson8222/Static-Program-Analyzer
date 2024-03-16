#include "pkb/writers/links/CallProcNameWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
CallProcNameWriter::CallProcNameWriter(std::shared_ptr<CallProcNameStore> store) : callProcNameStore(std::move(store)) {}

void CallProcNameWriter::addCallProcName(int statementNumber, std::string procName) {
    callProcNameStore->addLink(statementNumber, procName);
}

void CallProcNameWriter::addLink(int statementNumber, std::string procName) {
    addCallProcName(statementNumber, procName);
}

void CallProcNameWriter::clear() {
    callProcNameStore->clear();
}
// ai-gen end
