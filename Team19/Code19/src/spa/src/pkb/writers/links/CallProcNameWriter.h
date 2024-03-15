#pragma once

#include <memory>
#include <string>
#include "pkb/stores/links/ILinkWriter.h"
#include "pkb/stores/links/types/CallProcNameStore.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
class CallProcNameWriter : public ILinkWriter<int, std::string> {
private:
    std::shared_ptr<CallProcNameStore> callProcNameStore;
public:
    CallProcNameWriter(std::shared_ptr<CallProcNameStore> store);

    // Custom methods
    /**
     * @brief Adds a link between a statement and a procedure name.
     * @param statementNumber The statement number of the "Call" statement.
     * @param procName The name of the procedure called at the statement.
     */
    void addCallProcName(int statementNumber, std::string procName);

    // Inherited methods
    void addLink(int statementNumber, std::string procName) override;
    void clear() override;
};
// ai-gen end
