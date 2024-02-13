#pragma once

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/UsesPStore.h"
#include <memory>

class UsesPWriter : public IRelationshipWriter<std::string , std::string> {
private:
    std::shared_ptr<UsesPStore> usesPStore;

public:
    explicit UsesPWriter(std::shared_ptr<UsesPStore> store) : usesPStore(std::move(store)) {}

    void addRelationship(std::string proc, std::string var) override {
        addUsesP(proc, var);
    }

    void clear() override {
      usesPStore->clear();
    }

    void addUsesP(std::string proc, std::string var) {
      usesPStore->addRelationship(proc, var);
    }
};
