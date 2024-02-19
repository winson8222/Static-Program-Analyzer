#pragma once

#include <memory>
#include "pkb/stores/patterns/control/IControlPatternReader.h"
#include "pkb/stores/patterns/control/WhilePatternStore.h"

class WhilePatternReader: public IControlPatternReader {
    
private:
    std::shared_ptr<WhilePatternStore> whilePatternStore;
public:
    explicit WhilePatternReader(std::shared_ptr<WhilePatternStore> store) : whilePatternStore(std::move(store)) {}

    std::unordered_set<int> getStatementNumbersWithWhilePattern(const std::string& whilePattern) {
      return whilePatternStore->getStatementNumbersWithWhilePattern(whilePattern);
    };

    std::unordered_set<std::string> getAllWhilePatterns() {
      return whilePatternStore->getAllWhilePatterns();
    };

    std::string getWhilePattern(int statementNumber) {
      return whilePatternStore->getWhilePattern(statementNumber);
    };

    bool isEmpty() override {
      return whilePatternStore->isEmpty();
    };

    std::string getControlPattern(int statementNumber) override {
      return whilePatternStore->getWhilePattern(statementNumber);
    };

    std::unordered_set<int> getStatementNumbersWithControlPattern(const std::string& controlPattern) override {
      return whilePatternStore->getStatementNumbersWithWhilePattern(controlPattern);
    };

    bool contains(int statementNumber) override {
      return whilePatternStore->contains(statementNumber);
    };

    std::unordered_set<int> getAllStatementNumbers() override {
      return whilePatternStore->getAllStatementNumbers();
    };

    std::unordered_set<std::string> getAllControlPatterns() override {
      return whilePatternStore->getAllWhilePatterns();
    };
};