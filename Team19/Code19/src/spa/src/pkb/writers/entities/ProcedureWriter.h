#pragma once

#include <memory>
#include <string>
#include "pkb/stores/entities/types/ProcedureStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class ProcedureWriter: public IEntityWriter<std::string> {
private:
    std::shared_ptr<ProcedureStore> procedureStore;
public:
    explicit ProcedureWriter(std::shared_ptr<ProcedureStore> ps) : procedureStore(std::move(ps)) {}

    bool addEntity(std::string entity) override {
        return insertProcedure(entity);
    }

    void clear() override {
        procedureStore->clear();
    }

    /**
     * @brief Inserts a procedure into the store.
     * @param procedureName The name of the procedure to be inserted.
     * @return True if the procedure is successfully inserted, false otherwise.
     */
    bool insertProcedure(const std::string& procedureName) {
        return procedureStore->addEntity(procedureName);
    }
};
// ai-gen end
