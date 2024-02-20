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

    // Custom methods
    /**
     * @brief Adds a "Uses" relationship between a statement and a variable.
     * @param stmtNum The statement number of the statement that uses the variable.
     * @param var The variable that is used by the statement.
     */
    void addUsesS(int stmtNum, const std::string& var) {
      usesSStore->addRelationship(stmtNum, var);
    }
};
// ai-gen end
