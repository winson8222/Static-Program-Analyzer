#include "VariableReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
VariableReader::VariableReader(std::shared_ptr<VariableStore> store) {
  variableStore = std::move(store);
}

bool VariableReader::isEmpty() const  {
  return variableStore->isEmpty();
}

std::unordered_set<std::string> VariableReader::getAllEntities() const  {
  return variableStore->getAllEntities();
}

bool VariableReader::contains(std::string stmtNum) const  {
  return variableStore->contains(stmtNum);
}

std::unordered_set<std::string> VariableReader::getAllVariables() const {
  return variableStore->getAllEntities();
}

bool VariableReader::hasVariable(std::string stmtNum) const {
  return variableStore->contains(stmtNum);
}
// ai-gen end
