#include "ConstantReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
ConstantReader::ConstantReader(std::shared_ptr<ConstantStore> store) {
  constantStore = std::move(store);
}

bool ConstantReader::isEmpty() const  {
  return constantStore->isEmpty();
}

std::unordered_set<int> ConstantReader::getAllEntities() const  {
  return constantStore->getAllEntities();
}

bool ConstantReader::contains(int stmtNum) const  {
  return constantStore->contains(stmtNum);
}

std::unordered_set<int> ConstantReader::getAllConstants() const {
  return constantStore->getAllEntities();
}

bool ConstantReader::hasConstant(int constant) const {
  return constantStore->contains(constant);
}
// ai-gen end