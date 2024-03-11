#pragma once

#include <memory>

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/ModifiesPStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ModifiesPWriter : public IRelationshipWriter<std::string , std::string> {
private:
    std::shared_ptr<ModifiesPStore> modifiesPStore;

public:
    ModifiesPWriter(std::shared_ptr<ModifiesPStore> store);

    void addRelationship(std::string proc, std::string var) override;

    void clear() override;

    // Custom methods
    /**
     * @brief Adds a "Modifies" relationship between a procedure and a variable.
     * @param proc The procedure that modifies the variable.
     * @param var The variable that is modified by the procedure.
     */
    void addModifiesP(std::string proc, std::string var);
};
// ai-gen end
