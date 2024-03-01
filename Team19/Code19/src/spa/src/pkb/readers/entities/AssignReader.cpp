#include "AssignReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
AssignReader::AssignReader(std::shared_ptr<AssignStore> store) {
  assignStore = std::move(store);
}

bool AssignReader::isEmpty() const  {
  return assignStore->isEmpty();
}

std::unordered_set<int> AssignReader::getAllEntities() const  {
  return assignStore->getAllEntities();
}

bool AssignReader::contains(int stmtNum) const  {
  return assignStore->contains(stmtNum);
}

std::unordered_set<int> AssignReader::getAllAssigns() const {
  return assignStore->getAllEntities();
}

bool AssignReader::hasAssign(int stmtNum) const {
  return assignStore->contains(stmtNum);
}
// ai-gen end
