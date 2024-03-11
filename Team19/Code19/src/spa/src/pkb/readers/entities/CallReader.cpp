#include "CallReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
CallReader::CallReader(std::shared_ptr<CallStore> store) {
  callStore = std::move(store);
}

bool CallReader::isEmpty() const  {
  return callStore->isEmpty();
}

std::unordered_set<int> CallReader::getAllEntities() const  {
  return callStore->getAllEntities();
}

bool CallReader::contains(int stmtNum) const  {
  return callStore->contains(stmtNum);
}

std::unordered_set<int> CallReader::getAllCalls() const {
  return callStore->getAllEntities();
}

bool CallReader::hasCall(int stmtNum) const {
  return callStore->contains(stmtNum);
}
// ai-gen end
