#pragma once

#include <memory>
#include "pkb/stores/patterns/control/IControlPatternReader.h"
#include "pkb/stores/patterns/control/IfPatternStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class IfPatternReader: public IControlPatternReader {
private:
    std::shared_ptr<IfPatternStore> ifPatternStore;
public:
    explicit IfPatternReader(std::shared_ptr<IfPatternStore> store) : ifPatternStore(std::move(store)) {}

    // Custom methods
    /**
     * @brief Gets the statement numbers of the "If" patterns that match the given control variable.
     * @param controlVariable
     * @return unordered_set<int>: The set of statement numbers of all "If" patterns that match the given control variable.
     */
    std::unordered_set<int> getStatementNumbersOfIfControlVariable(const std::string& controlVariable) {
      return ifPatternStore->getStatementNumbersWithIfPattern(controlVariable);
    };

    /**
     * @brief Gets the "If" pattern of the given statement.
     * @param statementNumber
     * @return std::string: The control variable of the "If" pattern of the given statement.
     */
    std::unordered_set<std::string> getControlVariablesOfIfStatement(int statementNumber) {
      return ifPatternStore->getIfPatternsWithStatementNumber(statementNumber);
    };

    /**
     * @brief Checks if a specific "If" pattern exists for the given statement.
     * @return true if the "If" pattern exists, false otherwise.
     */
    bool hasStatementNumberWithIfPattern(int statementNumber) {
      return ifPatternStore->hasStatementNumberWithIfPattern(statementNumber);
    };

    /**
     * @brief Gets all statement numbers of "If" control variables.
     * @return unordered_set<int>: The set of statement numbers of all "If" control variables.
     */
    std::unordered_set<int> getAllStatementNumbersOfIfControlVariables() {
      return ifPatternStore->getAllStatementNumbers();
    };

    /**
     * @brief Gets the statement numbers of all "If" control variables.
     * @return unordered_set<int>: The set of statement numbers of all "If" control variables.
     */
    std::unordered_set<std::string> getAllIfControlVariables() {
      return ifPatternStore->getAllIfPatterns();
    };

    // Inherited methods
    /**
     * Check if the store is empty
     * @return true if the store is empty, false otherwise
     */
    bool isEmpty() override {
        return ifPatternStore->isEmpty();
    };

    std::unordered_set<int> getAllStatementNumbers() override {
        return ifPatternStore->getAllStatementNumbers();
    };

    std::unordered_set<std::string> getControlPatternsWithStatementNumber(int statementNumber) override {
      return ifPatternStore->getIfPatternsWithStatementNumber(statementNumber);
    };

    std::unordered_set<int> getStatementNumbersWithControlPattern(const std::string& controlPattern) override {
        return ifPatternStore->getStatementNumbersWithIfPattern(controlPattern);
    };

    bool hasStatementNumber(int statementNumber) override {
        return ifPatternStore->hasStatementNumberWithIfPattern(statementNumber);
    };

    bool hasControlPattern(const std::string& controlPattern) override {
        return ifPatternStore->hasIfPattern(controlPattern);
    };


    bool hasControlPatternAtStatement(int statementNumber, const std::string& controlPattern) override {
      return ifPatternStore->hasIfPatternAtStatement(statementNumber, controlPattern);
    };

    std::unordered_set<std::string> getAllControlPatterns() override {
        return ifPatternStore->getAllIfPatterns();
    };
};
// ai-gen end
