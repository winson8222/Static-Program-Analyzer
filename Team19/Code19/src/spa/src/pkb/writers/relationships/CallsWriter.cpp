#include "CallsWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
CallsWriter::CallsWriter(std::shared_ptr<CallsStore> store) : callsStore(std::move(store)) {}

void CallsWriter::addCalls(const std::string& caller, const std::string& callee) {
    callsStore->addRelationship(caller, callee);
}

void CallsWriter::addRelationship(const std::string& caller, const std::string& callee) {
    addCalls(caller, callee);
}

void CallsWriter::clear() {
    callsStore->clear();
}
// ai-gen end