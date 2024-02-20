#pragma once

#include "ControlPatternStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class IfPatternStore : public ControlPatternStore {
public:
    void addIfPattern(int statementNumber, const std::string& ifPattern) {
        addControlPattern(statementNumber, ifPattern);
    }

    std::string getIfPattern(int statementNumber) {
        return getControlPattern(statementNumber);
    }

    std::unordered_set<int> getStatementNumbersWithIfPattern(const std::string& ifPattern) {
        return getStatementNumbersWithControlPattern(ifPattern);
    }

    std::unordered_set<std::string> getAllIfPatterns() {
        return getAllControlPatterns();
    }
};
// ai-gen end
