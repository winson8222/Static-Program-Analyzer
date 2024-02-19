#pragma once

#include "ControlPatternStore.h"

class WhilePatternStore : public ControlPatternStore {
public:
    void addWhilePattern(int statementNumber, const std::string& whilePattern) {
        addControlPattern(statementNumber, whilePattern);
    }

    std::string getWhilePattern(int statementNumber) {
        return getControlPattern(statementNumber);
    }

    std::unordered_set<int> getStatementNumbersWithWhilePattern(const std::string& whilePattern) {
      return getStatementNumbersWithControlPattern(whilePattern);
    }

    std::unordered_set<std::string> getAllWhilePatterns() {
      return getAllControlPatterns();
    }
};