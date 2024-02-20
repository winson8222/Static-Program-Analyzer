#pragma once

#include <memory>
#include "pkb/stores/entities/types/AssignStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class AssignWriter: public IEntityWriter<int> {
private:
    std::shared_ptr<AssignStore> assignStore;
public:
    explicit AssignWriter(std::shared_ptr<AssignStore> as) : assignStore(std::move(as)) {}

    bool addEntity(int entity) override {
        return insertAssign(entity);
    }

    void clear() override {
        assignStore->clear();
    }

    /**
     * @brief Inserts an "Assign" statement into the store.
     * @param stmtNum The statement number of the assign statement.
     * @return True if the assign statement is successfully inserted, false otherwise.
     */
    bool insertAssign(int stmtNum) {
        return assignStore->addEntity(stmtNum);
    }
};
// ai-gen end
