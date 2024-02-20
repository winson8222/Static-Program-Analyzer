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
    std::string getControlVariableOfIfStatement(int statementNumber) {
      return ifPatternStore->getIfPattern(statementNumber);
    };

    /**
     * @brief Checks if a specific "If" pattern exists for the given statement.
     * @return true if the "If" pattern exists, false otherwise.
     */
    bool hasIfPattern(int statementNumber) {
      return ifPatternStore->contains(statementNumber);
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
    bool isEmpty() override {
      return ifPatternStore->isEmpty();
    };

    std::string getControlPattern(int statementNumber) override {
      return ifPatternStore->getIfPattern(statementNumber);
    };

    std::unordered_set<int> getStatementNumbersWithControlPattern(const std::string& controlPattern) override {
      return ifPatternStore->getStatementNumbersWithIfPattern(controlPattern);
    };

    bool contains(int statementNumber) override {
      return ifPatternStore->contains(statementNumber);
    };

    std::unordered_set<int> getAllStatementNumbers() override {
      return ifPatternStore->getAllStatementNumbers();
    };

    std::unordered_set<std::string> getAllControlPatterns() override {
      return ifPatternStore->getAllIfPatterns();
    };
};
// ai-gen end
