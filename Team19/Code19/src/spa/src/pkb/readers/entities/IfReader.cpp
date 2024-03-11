#include "IfReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
IfReader::IfReader(std::shared_ptr<IfStore> store) {
  ifStore = std::move(store);
}

bool IfReader::isEmpty() const  {
  return ifStore->isEmpty();
}

std::unordered_set<int> IfReader::getAllEntities() const  {
  return ifStore->getAllEntities();
}

bool IfReader::contains(int stmtNum) const  {
  return ifStore->contains(stmtNum);
}

std::unordered_set<int> IfReader::getAllIfs() const {
  return ifStore->getAllEntities();
}

bool IfReader::hasIf(int stmtNum) const {
  return ifStore->contains(stmtNum);
}
// ai-gen end
