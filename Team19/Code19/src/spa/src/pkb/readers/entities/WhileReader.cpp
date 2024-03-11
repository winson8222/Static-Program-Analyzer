#include "WhileReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
WhileReader::WhileReader(std::shared_ptr<WhileStore> store) {
  whileStore = std::move(store);
}

bool WhileReader::isEmpty() const  {
  return whileStore->isEmpty();
}

std::unordered_set<int> WhileReader::getAllEntities() const  {
  return whileStore->getAllEntities();
}

bool WhileReader::contains(int stmtNum) const  {
  return whileStore->contains(stmtNum);
}

std::unordered_set<int> WhileReader::getAllWhiles() const {
  return whileStore->getAllEntities();
}

bool WhileReader::hasWhile(int stmtNum) const {
  return whileStore->contains(stmtNum);
}
// ai-gen end
