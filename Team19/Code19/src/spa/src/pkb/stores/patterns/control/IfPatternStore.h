#pragma once

#include "ControlPatternStore.h"

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