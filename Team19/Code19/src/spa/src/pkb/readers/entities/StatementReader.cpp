#include "StatementReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
StatementReader::StatementReader(std::shared_ptr<StatementStore> store) {
  statementStore = std::move(store);
}

bool StatementReader::isEmpty() const  {
  return statementStore->isEmpty();
}

std::unordered_set<int> StatementReader::getAllEntities() const  {
  return statementStore->getAllEntities();
}

bool StatementReader::contains(int stmtNum) const  {
  return statementStore->contains(stmtNum);
}

std::unordered_set<int> StatementReader::getAllStatements() const {
  return statementStore->getAllEntities();
}

bool StatementReader::hasStatement(int stmtNum) const {
  return statementStore->contains(stmtNum);
}
// ai-gen end
