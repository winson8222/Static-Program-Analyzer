#pragma once

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/ModifiesPStore.h"
#include <memory>

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ModifiesPWriter : public IRelationshipWriter<std::string , std::string> {
private:
    std::shared_ptr<ModifiesPStore> modifiesPStore;

public:
    explicit ModifiesPWriter(std::shared_ptr<ModifiesPStore> store) : modifiesPStore(std::move(store)) {}

    void addRelationship(std::string proc, std::string var) override {
        addModifiesP(proc, var);
    }

    void clear() override {
      modifiesPStore->clear();
    }

    void addModifiesP(std::string proc, std::string var) {
      modifiesPStore->addRelationship(proc, var);
    }
};
// ai-gen end
