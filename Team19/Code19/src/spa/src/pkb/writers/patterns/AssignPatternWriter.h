#pragma once

#include <memory>

#include "pkb/stores/patterns/assign/IAssignPatternWriter.h"
#include "pkb/stores/patterns/assign/AssignPatternStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class AssignPatternWriter : public IAssignPatternWriter {
private:
    std::shared_ptr<AssignPatternStore> assignPatternStore;
public:
    AssignPatternWriter(std::shared_ptr<AssignPatternStore> store);

    /**
     * @brief Adds an "Assign" pattern to the store.
     * @param statementNumber The statement number of the assignment statement.
     * @param LHS The left hand side of the assignment statement.
     * @param RHS The right hand side of the assignment statement.
     */
    void addAssignPattern(int statementNumber, std::string LHS, std::string RHS) override;

    // Clears all assign patterns from the store.
    void clear() override;
};
// ai-gen end
