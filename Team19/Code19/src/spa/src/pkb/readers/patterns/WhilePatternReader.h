#pragma once

#include <memory>
#include "pkb/stores/patterns/control/IControlPatternReader.h"
#include "pkb/stores/patterns/control/WhilePatternStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class WhilePatternReader: public IControlPatternReader {
private:
    std::shared_ptr<WhilePatternStore> whilePatternStore;
public:
    explicit WhilePatternReader(std::shared_ptr<WhilePatternStore> store) : whilePatternStore(std::move(store)) {}

    // Custom methods
    /**
     * @brief Gets the statement numbers of the "While" patterns that match the given control variable.
     * @param controlVariable
     * @return unordered_set<int>: The set of statement numbers of all "While" patterns that match the given control variable.
     */
    std::unordered_set<int> getStatementNumbersOfWhileControlVariable(const std::string& controlVariable) {
      return whilePatternStore->getStatementNumbersWithWhilePattern(controlVariable);
    };

    /**
     * @brief Gets the "While" pattern of the given statement.
     * @param statementNumber
     * @return std::string: The control variable of the "While" pattern of the given statement.
     */
    std::unordered_set<std::string> getControlVariablesOfWhileStatement(int statementNumber) {
      return whilePatternStore->getWhilePatternsWithStatementNumber(statementNumber);
    };

    /**
     * @brief Checks while a specwhileic "While" pattern exists for the given statement.
     * @return true while the "While" pattern exists, false otherwise.
     */
    bool hasStatementNumberWithWhilePattern(int statementNumber) {
      return whilePatternStore->hasStatementNumberWithWhilePattern(statementNumber);
    };

    /**
     * @brief Gets all statement numbers of "While" control variables.
     * @return unordered_set<int>: The set of statement numbers of all "While" control variables.
     */
    std::unordered_set<int> getAllStatementNumbersOfWhileControlVariables() {
      return whilePatternStore->getAllStatementNumbers();
    };

    /**
     * @brief Gets the statement numbers of all "While" control variables.
     * @return unordered_set<int>: The set of statement numbers of all "While" control variables.
     */
    std::unordered_set<std::string> getAllWhileControlVariables() {
      return whilePatternStore->getAllWhilePatterns();
    };

    // Inherited methods
    /**
     * Check while the store is empty
     * @return true while the store is empty, false otherwise
     */
    bool isEmpty() override {
      return whilePatternStore->isEmpty();
    };

    std::unordered_set<int> getAllStatementNumbers() override {
      return whilePatternStore->getAllStatementNumbers();
    };

    std::unordered_set<std::string> getControlPatternsWithStatementNumber(int statementNumber) override {
      return whilePatternStore->getWhilePatternsWithStatementNumber(statementNumber);
    };

    std::unordered_set<int> getStatementNumbersWithControlPattern(const std::string& controlPattern) override {
      return whilePatternStore->getStatementNumbersWithWhilePattern(controlPattern);
    };

    bool hasStatementNumber(int statementNumber) override {
      return whilePatternStore->hasStatementNumberWithWhilePattern(statementNumber);
    };

    bool hasControlPattern(const std::string& controlPattern) override {
      return whilePatternStore->hasWhilePattern(controlPattern);
    };


    bool hasControlPatternAtStatement(int statementNumber, const std::string& controlPattern) override {
      return whilePatternStore->hasWhilePatternAtStatement(statementNumber, controlPattern);
    };

    std::unordered_set<std::string> getAllControlPatterns() override {
      return whilePatternStore->getAllWhilePatterns();
    };
};
// ai-gen end
