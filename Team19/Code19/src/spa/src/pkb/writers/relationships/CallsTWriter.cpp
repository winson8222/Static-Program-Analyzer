#include "CallsTWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
CallsTWriter::CallsTWriter(std::shared_ptr<CallsTStore> store) : callsTStore(std::move(store)) {}

void CallsTWriter::addCallsT( std::string caller,  std::string callee) {
    callsTStore->addRelationship(caller, callee);
}

void CallsTWriter::addRelationship( std::string caller,  std::string callee) {
    addCallsT(caller, callee);
}

void CallsTWriter::clear() {
    callsTStore->clear();
}
// ai-gen end