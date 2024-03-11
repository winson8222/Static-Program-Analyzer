#pragma once

#include <memory>

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/ProcedureStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ProcedureReader: public IEntityReader<std::string> {
private:
    std::shared_ptr<ProcedureStore> procedureStore;
public:
    ProcedureReader(std::shared_ptr<ProcedureStore> store);
    bool isEmpty() const override;
    std::unordered_set<std::string> getAllEntities() const override;
    bool contains(std::string stmtNum) const override;

    // Custom methods
    /**
     * @brief Gets all procedure names.
     * @return unordered_set<string>: The set of all procedure names.
     */
    std::unordered_set<std::string> getAllProcedures() const;
    /**
     * @brief Checks if a specific procedure exists.
     * @param proc The procedure name to check.
     * @return true if the procedure exists, false otherwise.
     */
    bool hasProcedure(std::string proc) const;
};
// ai-gen end
