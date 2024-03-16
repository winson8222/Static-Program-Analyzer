#pragma once

#include <memory>
#include <string>
#include "pkb/stores/links/ILinkWriter.h"
#include "pkb/stores/links/types/PrintVarNameStore.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class PrintVarNameWriter : public ILinkWriter<int, std::string> {
private:
    std::shared_ptr<PrintVarNameStore> printVarNameStore;
public:
    PrintVarNameWriter(std::shared_ptr<PrintVarNameStore> store);

    // Custom methods
    /**
     * @brief Adds a link between a print statement and a variable name.
     * @param statementNumber The statement number of the "Print" statement.
     * @param varName The name of the variable printed at the statement.
     */
    void addPrintVarName(int statementNumber, std::string varName);

    // Inherited methods
    void addLink(int statementNumber, std::string varName) override;
    void clear() override;
};
// ai-gen end
