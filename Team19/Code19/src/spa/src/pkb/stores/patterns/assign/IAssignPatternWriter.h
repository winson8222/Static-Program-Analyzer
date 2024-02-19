#pragma once

#include <unordered_map>
#include <unordered_set>

class IAssignPatternWriter {
public:
    virtual void addAssignPattern(int statementNumber, std::string LHS, std::string RHS) = 0;

    virtual void clear() = 0;
};
