#pragma once

#include <memory>

#include "pkb/stores/links/ILinkReader.h"
#include "pkb/stores/links/types/CallProcNameStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class CallProcNameReader: public ILinkReader<int, std::string> {
private:
    std::shared_ptr<CallProcNameStore> callProcNameStore;
public:
    explicit CallProcNameReader(std::shared_ptr<CallProcNameStore> store);

    // Custom methods
    /**
     * @brief Get the set of all statement numbers that call a given procedure.
     * @param procName The name of the procedure.
     * @return The set of all statement numbers that call the given procedure.
     */
    std::unordered_set<int> getCallers(std::string procName);

    /**
     * @brief Get the name of the procedure called at a given statement.
     * @param statementNumber The statement number of the "Call" statement.
     * @return The name of the procedure called at the given statement.
     */
    std::string getCalledProcedureName(int statementNumber);

    /**
     * @brief Check if a given statement calls a given procedure.
     * @return True if the statement calls the procedure, false otherwise.
     */
    bool isCalled(int statementNumber, std::string procName);

    // Inherited methods
    bool isEmpty() override;
    bool hasLink(int statementNumber, std::string procName) override;
    std::unordered_set<int> getLinker(std::string procName) override;
    std::string getLinked(int statementNumber) override;
};
// ai-gen end
