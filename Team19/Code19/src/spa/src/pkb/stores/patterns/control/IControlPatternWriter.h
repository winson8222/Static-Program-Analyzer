#pragma once

#include <string>

class IControlPatternWriter {
public:
    virtual void addControlPattern(int statementNumber, const std::string& controlPattern) = 0;

    virtual void clear() = 0;
};