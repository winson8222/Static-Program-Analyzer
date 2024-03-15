#pragma once

#include <memory>
#include <string>
#include "pkb/stores/links/ILinkWriter.h"
#include "pkb/stores/links/types/ReadVarNameStore.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class ReadVarNameWriter : public ILinkWriter<int, std::string> {
private:
    std::shared_ptr<ReadVarNameStore> readVarNameStore;
public:
    ReadVarNameWriter(std::shared_ptr<ReadVarNameStore> store);

    // Custom methods
    /**
     * @brief Adds a link between a read statement and a variable name.
     * @param statementNumber The statement number of the "Read" statement.
     * @param varName The name of the variable read at the statement.
     */
    void addReadVarName(int statementNumber, std::string varName);

    // Inherited methods
    void addLink(int statementNumber, std::string varName) override;
    void clear() override;
};
// ai-gen end
