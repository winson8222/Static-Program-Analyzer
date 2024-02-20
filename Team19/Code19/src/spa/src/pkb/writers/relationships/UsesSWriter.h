#pragma once

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/UsesSStore.h"
#include <memory>

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class UsesSWriter : public IRelationshipWriter<int , std::string> {
private:
    std::shared_ptr<UsesSStore> usesSStore;

public:
    explicit UsesSWriter(std::shared_ptr<UsesSStore> store) : usesSStore(std::move(store)) {}

    void addRelationship(int stmtNum, std::string var) override {
        addUsesS(stmtNum, var);
    }

    void clear() override {
      usesSStore->clear();
    }

    void addUsesS(int stmtNum, std::string var) {
      usesSStore->addRelationship(stmtNum, var);
    }
};
// ai-gen end
