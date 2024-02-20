#pragma once

#include <string>
#include <unordered_set>

#include "pkb/templates/TemplateMapSet.h"

#include "IControlPatternReader.h"
#include "IControlPatternWriter.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class ControlPatternStore: public IControlPatternReader, public IControlPatternWriter {
private:
    TemplateMapSet<int, std::string> controlPatterns;
    TemplateMapSet<std::string, int> reverseControlPatterns;
public:
    /**
     * Check if the store is empty
     * @return true if the store is empty, false otherwise
     */
    bool isEmpty() override {
        return controlPatterns.isEmpty() && reverseControlPatterns.isEmpty();
    };

    /**
     * Get all statement numbers in the store with control patterns
     * @return unordered_set<int>: Set of statement numbers
     */
    std::unordered_set<int> getAllStatementNumbers() override {
        return controlPatterns.getKeys();
    };

    /**
     * Get all control variables with a given statement number
     * @param statementNumber
     * @return unordered_set<string>: Set of control variables
     */
    std::unordered_set<std::string> getControlPatternsWithStatementNumber(int statementNumber) override {
      return controlPatterns.getValuesByKey(statementNumber);
    };

    /**
     * Get all statement numbers with a given control pattern
     * @param controlPattern
     * @return unordered_set<int>: Set of statement numbers
     */
    std::unordered_set<int> getStatementNumbersWithControlPattern(const std::string& controlPattern) override {
      return reverseControlPatterns.getValuesByKey(controlPattern);
    };

    /**
     * Check if the store has a given statement number
     * @param statementNumber
     * @return true if the store has the statement number, false otherwise
     */
    bool hasStatementNumber(int statementNumber) override {
        return controlPatterns.hasKey(statementNumber);
    };

    /**
     * Check if the store has a given control pattern
     * @param controlPattern
     * @return true if the store has the control pattern, false otherwise
     */
    bool hasControlPattern(const std::string& controlPattern) override {
        return reverseControlPatterns.hasKey(controlPattern);
    };

    /**
     * Check if the store has a given control pattern at a given statement number
     * @param statementNumber
     * @param controlPattern
     * @return true if the store has the control pattern at the statement number, false otherwise
     */
    bool hasControlPatternAtStatement(int statementNumber, const std::string& controlPattern) override {
        return controlPatterns.hasKeyValue(statementNumber, controlPattern);
    };

    /**
     * Get all control patterns in the store
     * @return unordered_set<string>: Set of control patterns
     */
    std::unordered_set<std::string> getAllControlPatterns() override {
        return reverseControlPatterns.getKeys();
    };

    /**
     * Add a control pattern to the store
     * @param statementNumber
     * @param controlPattern
     */
    void addControlPattern(int statementNumber, const std::string& controlPattern) override {
          controlPatterns.addKeyValue(statementNumber, controlPattern);
          reverseControlPatterns.addKeyValue(controlPattern, statementNumber);
    };

    /**
     * Clear all control patterns from the store
     */
    void clear() override {
        controlPatterns.clear();
        reverseControlPatterns.clear();
    }
};
// ai-gen end
