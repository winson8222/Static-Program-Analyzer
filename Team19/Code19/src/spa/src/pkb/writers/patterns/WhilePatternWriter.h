#pragma once

#include <memory>
#include "pkb/stores/patterns/control/IControlPatternWriter.h"
#include "pkb/stores/patterns/control/WhilePatternStore.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
class WhilePatternWriter: public IControlPatternWriter {
private:
    std::shared_ptr<WhilePatternStore> whilePatternStore;
public:
    explicit WhilePatternWriter(std::shared_ptr<WhilePatternStore> store) : whilePatternStore(std::move(store)) {}

    void addWhilePattern(int statementNumber, const std::string& whilePattern) {
        whilePatternStore->addWhilePattern(statementNumber, whilePattern);
    }

    // Clears all while patterns from the store.
    void clear() override {
        whilePatternStore->clear();
    }

    void addControlPattern(int statementNumber, const std::string& controlPattern) override {
        addWhilePattern(statementNumber, controlPattern);
    }
};
// ai-gen end
