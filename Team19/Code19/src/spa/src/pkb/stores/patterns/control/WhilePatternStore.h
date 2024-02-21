#pragma once

#include "ControlPatternStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class WhilePatternStore : public ControlPatternStore {
public:
    void addWhilePattern(int statementNumber, const std::string& whilePattern) {
        addControlPattern(statementNumber, whilePattern);
    }

    std::unordered_set<std::string> getWhilePatternsWithStatementNumber(int statementNumber) {
        return getControlPatternsWithStatementNumber(statementNumber);
    }

    std::unordered_set<int> getStatementNumbersWithWhilePattern(const std::string& whilePattern) {
      return getStatementNumbersWithControlPattern(whilePattern);
    }

    std::unordered_set<std::string> getAllWhilePatterns() {
      return getAllControlPatterns();
    }

    std::unordered_set<int> getAllStatementNumbersWithWhilePattern() {
      return getAllStatementNumbers();
    }

    bool hasWhilePatternAtStatement(int statementNumber, const std::string& whilePattern) {
      return hasControlPatternAtStatement(statementNumber, whilePattern);
    }

    bool hasWhilePattern(const std::string& whilePattern) {
      return hasControlPattern(whilePattern);
    }

    bool hasStatementNumberWithWhilePattern(int statementNumber) {
      return hasStatementNumber(statementNumber);
    }
};
// ai-gen end
