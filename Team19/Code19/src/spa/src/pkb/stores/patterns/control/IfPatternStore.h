#pragma once

#include "ControlPatternStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class IfPatternStore : public ControlPatternStore {
public:
    void addIfPattern(int statementNumber, const std::string& ifPattern) {
      addControlPattern(statementNumber, ifPattern);
    }

    std::unordered_set<std::string> getIfPatternsWithStatementNumber(int statementNumber) {
      return getControlPatternsWithStatementNumber(statementNumber);
    }

    std::unordered_set<int> getStatementNumbersWithIfPattern(const std::string& ifPattern) {
      return getStatementNumbersWithControlPattern(ifPattern);
    }

    std::unordered_set<std::string> getAllIfPatterns() {
      return getAllControlPatterns();
    }

    std::unordered_set<int> getAllStatementNumbersWithIfPattern() {
      return getAllStatementNumbers();
    }

    bool hasIfPatternAtStatement(int statementNumber, const std::string& ifPattern) {
      return hasControlPatternAtStatement(statementNumber, ifPattern);
    }

    bool hasIfPattern(const std::string& ifPattern) {
      return hasControlPattern(ifPattern);
    }

    bool hasStatementNumberWithIfPattern(int statementNumber) {
      return hasStatementNumber(statementNumber);
    }
};
// ai-gen end
