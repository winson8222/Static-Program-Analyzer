#pragma once

#include <string>

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class IControlPatternWriter {
public:
    virtual void addControlPattern(int statementNumber, const std::string& controlPattern) = 0;

    virtual void clear() = 0;
};
// ai-gen end
