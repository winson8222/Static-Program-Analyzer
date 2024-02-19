#pragma once

#include <memory>

#include "pkb/stores/patterns/control/IControlPatternWriter.h"
#include "pkb/stores/patterns/control/IfPatternStore.h"

class IfPatternWriter: public IControlPatternWriter {
private:
    std::shared_ptr<IfPatternStore> ifPatternStore;
public:
    explicit IfPatternWriter(std::shared_ptr<IfPatternStore> store) : ifPatternStore(std::move(store)) {}

    void addIfPattern(int statementNumber, const std::string& ifPattern) {
        ifPatternStore->addIfPattern(statementNumber, ifPattern);
    }

    // Clears all if patterns from the store.
    void clear() override {
        ifPatternStore->clear();
    }

    void addControlPattern(int statementNumber, const std::string& controlPattern) override {
        addIfPattern(statementNumber, controlPattern);
    }
};