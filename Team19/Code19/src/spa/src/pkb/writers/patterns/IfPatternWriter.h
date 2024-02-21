#pragma once

#include <memory>

#include "pkb/stores/patterns/control/IControlPatternWriter.h"
#include "pkb/stores/patterns/control/IfPatternStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class IfPatternWriter: public IControlPatternWriter {
private:
    std::shared_ptr<IfPatternStore> ifPatternStore;
public:
    explicit IfPatternWriter(std::shared_ptr<IfPatternStore> store) : ifPatternStore(std::move(store)) {}

    /**
     * @brief Adds an "If" control variable to the store.
     * @param statementNumber The statement number of the if statement.
     * @param ifControlVariable The control variable of the if statement.
     */
    void addIfControlVariable(int statementNumber, const std::string& ifControlVariable) {
        ifPatternStore->addIfPattern(statementNumber, ifControlVariable);
    }

    // Clears all if patterns from the store.
    void clear() override {
        ifPatternStore->clear();
    }

    void addControlPattern(int statementNumber, const std::string& controlPattern) override {
      addIfControlVariable(statementNumber, controlPattern);
    }
};
// ai-gen end
