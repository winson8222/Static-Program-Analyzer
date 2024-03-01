#include "ReadReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
ReadReader::ReadReader(std::shared_ptr<ReadStore> store) {
  readStore = std::move(store);
}

bool ReadReader::isEmpty() const  {
  return readStore->isEmpty();
}

std::unordered_set<int> ReadReader::getAllEntities() const  {
  return readStore->getAllEntities();
}

bool ReadReader::contains(int stmtNum) const  {
  return readStore->contains(stmtNum);
}

std::unordered_set<int> ReadReader::getAllReads() const {
  return readStore->getAllEntities();
}

bool ReadReader::hasRead(int stmtNum) const {
  return readStore->contains(stmtNum);
}
// ai-gen end
