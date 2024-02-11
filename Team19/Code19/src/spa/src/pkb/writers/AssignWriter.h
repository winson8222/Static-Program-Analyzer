#pragma once

#include <memory>
#include "pkb/stores/entities/types/AssignStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

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

    bool insertAssign(int stmtNum) {
        return assignStore->addEntity(stmtNum);
    }
};
