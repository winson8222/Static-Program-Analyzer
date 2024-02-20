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

    std::unordered_set<int> getStatementNumbersWithIfPattern(const std::string& ifPattern) {
        return ifPatternStore->getStatementNumbersWithIfPattern(ifPattern);
    };

    std::unordered_set<std::string> getAllIfPatterns() {
        return ifPatternStore->getAllIfPatterns();
    };

    std::string getIfPattern(int statementNumber) {
        return ifPatternStore->getIfPattern(statementNumber);
    };

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
