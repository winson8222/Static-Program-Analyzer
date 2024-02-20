#pragma once

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/ProcedureStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ProcedureReader: public IEntityReader<std::string> {
private:
    std::shared_ptr<ProcedureStore> procedureStore;
public:
    explicit ProcedureReader(std::shared_ptr<ProcedureStore> store) {
      procedureStore = std::move(store);
    }

    bool isEmpty() const override {
        return procedureStore->isEmpty();
    }

    std::unordered_set<std::string> getAllEntities() const override {
        return getAllProcedures();
    }

    bool contains(std::string stmtNum) const override {
      return hasProcedure(stmtNum);
    }

    std::unordered_set<std::string> getAllProcedures() const {
      return procedureStore->getAllEntities();
    }

    bool hasProcedure(std::string proc) const {
      return procedureStore->contains(proc);
    }
};
// ai-gen end
