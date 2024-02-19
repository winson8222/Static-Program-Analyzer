#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

class IAssignPatternReader {
public:
    virtual bool isEmpty() = 0;

    virtual std::string getLHS(int statementNumber) = 0;

    virtual std::string getRHS(int statementNumber) = 0;

    virtual std::unordered_map<int, std::pair<std::string, std::string>> getAllPatterns() = 0;

    virtual std::unordered_set<int> getAllStatementNumbers() = 0;

    virtual std::pair<std::string, std::string> getPattern(int statementNumber) = 0;

    virtual bool contains(int statementNumber) = 0;

    virtual std::unordered_set<int> getStatementNumbersWithLHS(const std::string& LHS) = 0;

    virtual std::unordered_set<int> getStatementNumbersWithRHS(const std::string& RHS) = 0;

    virtual std::unordered_set<int> getStatementNumbersWithPartialRHS(const std::string& partialRHS) = 0;

    virtual std::unordered_set<int> getStatementNumbersWithLHSRHS (const std::string& LHS, const std::string& RHS) = 0;

    virtual std::unordered_set<int> getStatementNumbersWithLHSPartialRHS (const std::string& LHS, const std::string& partialRHS) = 0;
};
