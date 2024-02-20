#pragma once

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/ModifiesSStore.h"
#include <memory>

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ModifiesSWriter : public IRelationshipWriter<int , std::string> {
private:
    std::shared_ptr<ModifiesSStore> modifiesSStore;

public:
    explicit ModifiesSWriter(std::shared_ptr<ModifiesSStore> store) : modifiesSStore(std::move(store)) {}

    void addRelationship(int stmtNum, std::string var) override {
        addModifiesP(stmtNum, var);
    }

    void clear() override {
      modifiesSStore->clear();
    }

    void addModifiesP(int stmtNum, std::string var) {
      modifiesSStore->addRelationship(stmtNum, var);
    }
};
// ai-gen end
