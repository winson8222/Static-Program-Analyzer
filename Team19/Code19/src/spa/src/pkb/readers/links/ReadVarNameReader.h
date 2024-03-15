#pragma once

#include <memory>

#include "pkb/stores/links/ILinkReader.h"
#include "pkb/stores/links/types/ReadVarNameStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ReadVarNameReader: public ILinkReader<int, std::string> {
private:
    std::shared_ptr<ReadVarNameStore> readVarNameStore;
public:
    explicit ReadVarNameReader(std::shared_ptr<ReadVarNameStore> store);

    // Custom methods
    /**
     * @brief Get the set of all statement numbers that read a given variable.
     * @param varName The name of the variable.
     * @return The set of all statement numbers that read the given variable.
     */
    std::unordered_set<int> getReaders(std::string varName) const;

    /**
     * @brief Get the name of the variable read at a given statement.
     * @param statementNumber The statement number of the "Read" statement.
     * @return The name of the variable read at the given statement.
     */
    std::unordered_set<std::string> getReadVariableName(int statementNumber) const;

    /**
     * @brief Check if a given statement reads a given variable.
     * @return True if the statement reads the variable, false otherwise.
     */
    bool isRead(int statementNumber, std::string varName) const;

    // Inherited methods
    bool isEmpty() override;
    bool hasLink(int statementNumber, std::string varName) override;
    std::unordered_set<int> getLinker(std::string varName) override;
    std::string getLinked(int statementNumber) override;
};
