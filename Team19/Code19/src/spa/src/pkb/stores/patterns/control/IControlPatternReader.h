#pragma once

#include <string>
#include <unordered_set>

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class IControlPatternReader {
public:
    virtual bool isEmpty() = 0;

    virtual std::unordered_set<std::string> getControlPatternsWithStatementNumber(int statementNumber) = 0;

    virtual std::unordered_set<int> getStatementNumbersWithControlPattern(const std::string& controlPattern) = 0;

    virtual bool hasControlPatternAtStatement(int statementNumber, const std::string& controlPattern) = 0;

    virtual bool hasStatementNumber(int statementNumber) = 0;

    virtual bool hasControlPattern(const std::string& controlPattern) = 0;

    virtual std::unordered_set<int> getAllStatementNumbers() = 0;

    virtual std::unordered_set<std::string> getAllControlPatterns() = 0;
};
// ai-gen end
