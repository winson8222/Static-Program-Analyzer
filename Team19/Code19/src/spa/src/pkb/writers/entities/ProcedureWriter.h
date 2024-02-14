#pragma once

#include <memory>
#include <string>
#include "pkb/stores/entities/types/ProcedureStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

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

    bool insertProcedure(const std::string& procedureName) {
        return procedureStore->addEntity(procedureName);
    }
};
