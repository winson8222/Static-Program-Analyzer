#pragma once

#include <unordered_map>
#include <unordered_set>
#include <string>

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class IAssignPatternWriter {
public:
    virtual void addAssignPattern(int statementNumber, std::string LHS, std::string RHS) = 0;

    virtual void clear() = 0;
};
// ai-gen end
