#pragma once

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/UsesPStore.h"
#include <memory>

// ai-gen start(copilot, 2, e)
// prompt: used copilot
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

    // Custom methods
    /**
     * @brief Adds a "Uses" relationship between a procedure and a variable.
     * @param proc The procedure that uses the variable.
     * @param var The variable that is used by the procedure.
     */
    void addUsesP(const std::string& proc, const std::string& var) {
      usesPStore->addRelationship(proc, var);
    }
};
// ai-gen end
