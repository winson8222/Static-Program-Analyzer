#pragma once

#include <memory>

#include "pkb/stores/entities/IEntityReader.h"
#include "pkb/stores/entities/types/StatementStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class StatementReader: public IEntityReader<int> {
private:
    std::shared_ptr<StatementStore> statementStore;
public:
    StatementReader(std::shared_ptr<StatementStore> store);

    bool isEmpty() const override;

    std::unordered_set<int> getAllEntities() const override;

    bool contains(int stmtNum) const override;

    // Custom methods
    /**
     * @brief Gets all statement numbers.
     * @return unordered_set<int>: The set of all statement numbers.
     */
    std::unordered_set<int> getAllStatements() const;

    /**
     * @brief Checks if a specific statement exists.
     * @param stmtNum The statement number to check.
     * @return true if the statement exists, false otherwise.
     */
    bool hasStatement(int stmtNum) const;
};
// ai-gen end
