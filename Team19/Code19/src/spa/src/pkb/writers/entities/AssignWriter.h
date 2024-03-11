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
    AssignWriter(std::shared_ptr<AssignStore> as);

    bool addEntity(int entity) override;

    void clear() override;

    /**
     * @brief Inserts an "Assign" statement into the store.
     * @param stmtNum The statement number of the assign statement.
     * @return True if the assign statement is successfully inserted, false otherwise.
     */
    bool insertAssign(int stmtNum);
};
// ai-gen end
