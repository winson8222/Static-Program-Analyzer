#include "PrintReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
PrintReader::PrintReader(std::shared_ptr<PrintStore> store) {
  printStore = std::move(store);
}

bool PrintReader::isEmpty() const  {
  return printStore->isEmpty();
}

std::unordered_set<int> PrintReader::getAllEntities() const  {
  return printStore->getAllEntities();
}

bool PrintReader::contains(int stmtNum) const  {
  return printStore->contains(stmtNum);
}

std::unordered_set<int> PrintReader::getAllPrints() const {
  return printStore->getAllEntities();
}

bool PrintReader::hasPrint(int stmtNum) const {
  return printStore->contains(stmtNum);
}
// ai-gen end
