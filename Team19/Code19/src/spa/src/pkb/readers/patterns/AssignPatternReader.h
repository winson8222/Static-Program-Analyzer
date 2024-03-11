#pragma once

#include <memory>

#include "pkb/stores/patterns/assign/IAssignPatternReader.h"
#include "pkb/stores/patterns/assign/AssignPatternStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class AssignPatternReader : public IAssignPatternReader {
private:
    std::shared_ptr<AssignPatternStore> assignPatternStore;
public:
    AssignPatternReader(std::shared_ptr<AssignPatternStore> store);

    // Inherited methods
    bool isEmpty() override;

    std::string getLHS(int statementNumber) override;

    std::string getRHS(int statementNumber) override;

    std::unordered_map<int, std::pair<std::string, std::string>> getAllPatterns() override;

    std::pair<std::string, std::string> getPattern(int statementNumber) override;

    bool contains(int statementNumber) override;

    std::unordered_set<int> getAllStatementNumbers() override;

    std::unordered_set<int> getStatementNumbersWithLHS(const std::string& LHS) override;

    std::unordered_set<int> getStatementNumbersWithRHS(const std::string& RHS) override;

    std::unordered_set<int> getStatementNumbersWithPartialRHS(const std::string& partialRHS) override;

    std::unordered_set<int> getStatementNumbersWithLHSRHS (const std::string& LHS, const std::string& RHS) override;

    std::unordered_set<int> getStatementNumbersWithLHSPartialRHS (const std::string& LHS, const std::string& partialRHS) override;
};
// ai-gen end
