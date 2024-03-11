#pragma once

#include <memory>

#include "pkb/stores/relationships/IRelationshipWriter.h"
#include "pkb/stores/relationships/types/UsesPStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class UsesPWriter : public IRelationshipWriter<std::string , std::string> {
private:
    std::shared_ptr<UsesPStore> usesPStore;

public:
    UsesPWriter(std::shared_ptr<UsesPStore> store);
    void addRelationship(std::string proc, std::string var) override;
    void clear() override;

    // Custom methods
    /**
     * @brief Adds a "Uses" relationship between a procedure and a variable.
     * @param proc The procedure that uses the variable.
     * @param var The variable that is used by the procedure.
     */
    void addUsesP(const std::string& proc, const std::string& var);
};
// ai-gen end
