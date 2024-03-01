#include "ProcedureReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
ProcedureReader::ProcedureReader(std::shared_ptr<ProcedureStore> store) {
  procedureStore = std::move(store);
}

bool ProcedureReader::isEmpty() const  {
  return procedureStore->isEmpty();
}

std::unordered_set<std::string> ProcedureReader::getAllEntities() const  {
  return procedureStore->getAllEntities();
}

bool ProcedureReader::contains(std::string stmtNum) const  {
  return procedureStore->contains(stmtNum);
}

std::unordered_set<std::string> ProcedureReader::getAllProcedures() const {
  return procedureStore->getAllEntities();
}

bool ProcedureReader::hasProcedure(std::string stmtNum) const {
  return procedureStore->contains(stmtNum);
}
// ai-gen end
