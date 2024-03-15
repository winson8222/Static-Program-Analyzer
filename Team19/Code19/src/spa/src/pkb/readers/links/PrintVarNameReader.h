#pragma once

#include <memory>

#include "pkb/stores/links/ILinkReader.h"
#include "pkb/stores/links/types/PrintVarNameStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class PrintVarNameReader: public ILinkReader<int, std::string> {
private:
    std::shared_ptr<PrintVarNameStore> printVarNameStore;
public:
    explicit PrintVarNameReader(std::shared_ptr<PrintVarNameStore> store);

    // Custom methods
    /**
     * @brief Get the set of all statement numbers that print a given variable.
     * @param varName The name of the variable.
     * @return The set of all statement numbers that print the given variable.
     */
    std::unordered_set<int> getPrinters(std::string varName) const;

    /**
     * @brief Get the name of the variable print at a given statement.
     * @param statementNumber The statement number of the "Print" statement.
     * @return The name of the variable print at the given statement.
     */
    std::unordered_set<std::string> getPrintVariableName(int statementNumber) const;

    /**
     * @brief Check if a given statement prints a given variable.
     * @return True if the statement prints the variable, false otherwise.
     */
    bool isPrinted(int statementNumber, std::string varName) const;

    // Inherited methods
    bool isEmpty() override;
    bool hasLink(int statementNumber, std::string varName) override;
    std::unordered_set<int> getLinker(std::string varName) override;
    std::string getLinked(int statementNumber) override;
};
