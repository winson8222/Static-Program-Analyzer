#pragma once

#include <memory>

#include "pkb/stores/patterns/assign/IAssignPatternReader.h"
#include "pkb/stores/patterns/assign/AssignPatternStore.h"

class AssignPatternReader : public IAssignPatternReader {
private:
    std::shared_ptr<AssignPatternStore> assignPatternStore;
public:
    explicit AssignPatternReader(std::shared_ptr<AssignPatternStore> store) : assignPatternStore(std::move(store)) {}

    bool isEmpty() override {
        return assignPatternStore->isEmpty();
    }

    std::string getLHS(int statementNumber) override {
        return assignPatternStore->getLHS(statementNumber);
    }

    std::string getRHS(int statementNumber) override {
        return assignPatternStore->getRHS(statementNumber);
    }

    std::unordered_map<int, std::pair<std::string, std::string>> getAllPatterns() override {
        return assignPatternStore->getAllPatterns();
    }

    std::pair<std::string, std::string> getPattern(int statementNumber) override {
        return assignPatternStore->getPattern(statementNumber);
    }

    bool contains(int statementNumber) override {
        return assignPatternStore->contains(statementNumber);
    }

    std::unordered_set<int> getStatementNumbersWithLHS(const std::string& LHS) override {
        return assignPatternStore->getStatementNumbersWithLHS(LHS);
    }

    std::unordered_set<int> getStatementNumbersWithRHS(const std::string& RHS) override {
        return assignPatternStore->getStatementNumbersWithRHS(RHS);
    }

    std::unordered_set<int> getStatementNumbersWithPartialRHS(const std::string& partialRHS) override {
        return assignPatternStore->getStatementNumbersWithPartialRHS(partialRHS);
    }

    std::unordered_set<int> getStatementNumbersWithLHSRHS (const std::string& LHS, const std::string& RHS) override {
        return assignPatternStore->getStatementNumbersWithLHSRHS(LHS, RHS);
    }

    std::unordered_set<int> getStatementNumbersWithLHSPartialRHS (const std::string& LHS, const std::string& partialRHS) override {
        return assignPatternStore->getStatementNumbersWithLHSPartialRHS(LHS, partialRHS);
    }
};
