#include "CallsWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
CallsWriter::CallsWriter(std::shared_ptr<CallsStore> store) : callsStore(std::move(store)) {}

void CallsWriter::addCalls( std::string caller,  std::string callee) {
    callsStore->addRelationship(caller, callee);
}

void CallsWriter::addRelationship( std::string caller,  std::string callee) {
    addCalls(caller, callee);
}

void CallsWriter::clear() {
    callsStore->clear();
}
// ai-gen end