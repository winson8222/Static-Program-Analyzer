#pragma once

#include <memory>
#include "pkb/stores/entities/types/ConstantStore.h"
#include "pkb/stores/entities/IEntityWriter.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class ConstantWriter: public IEntityWriter<int> {
private:
    std::shared_ptr<ConstantStore> constantStore;
public:
    explicit ConstantWriter(std::shared_ptr<ConstantStore> cs) : constantStore(std::move(cs)) {}

    bool addEntity(int entity) override {
        return insertConstant(entity);
    }

    void clear() override {
        constantStore->clear();
    }

    bool insertConstant(int constantValue) {
        return constantStore->addEntity(constantValue);
    }
};
// ai-gen end
