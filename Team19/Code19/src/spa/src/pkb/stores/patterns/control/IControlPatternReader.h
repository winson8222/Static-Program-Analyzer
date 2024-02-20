#pragma once

#include <string>
#include <unordered_set>

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class IControlPatternReader {
public:
    virtual bool isEmpty() = 0;

    virtual std::string getControlPattern(int statementNumber) = 0;

    virtual std::unordered_set<int> getStatementNumbersWithControlPattern(const std::string& controlPattern) = 0;

    virtual bool contains(int statementNumber) = 0;

    virtual std::unordered_set<int> getAllStatementNumbers() = 0;

    virtual std::unordered_set<std::string> getAllControlPatterns() = 0;
};
// ai-gen end
