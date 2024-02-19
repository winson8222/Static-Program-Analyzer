#pragma once

#include <string>
#include <unordered_set>

#include "IControlPatternReader.h"
#include "IControlPatternWriter.h"

class ControlPatternStore: public IControlPatternReader, public IControlPatternWriter {
private:
    std::unordered_map<int, std::string> controlPatterns;
public:
    bool isEmpty() override {
        return controlPatterns.empty();
    };

    std::string getControlPattern(int statementNumber) override {
        return controlPatterns[statementNumber];
    };

    bool contains(int statementNumber) override {
        return controlPatterns.find(statementNumber) != controlPatterns.end();
    };

    std::unordered_set<int> getStatementNumbersWithControlPattern(const std::string& controlPattern) override {
        std::unordered_set<int> statementNumbers;
        for (auto const& [statementNumber, pattern] : controlPatterns) {
            if (pattern == controlPattern) {
                statementNumbers.insert(statementNumber);
            }
        }
        return statementNumbers;
    };

    std::unordered_set<int> getAllStatementNumbers() override {
        std::unordered_set<int> statementNumbers;
        for (auto const& [statementNumber, pattern] : controlPatterns) {
            statementNumbers.insert(statementNumber);
        }
        return statementNumbers;
    };

    std::unordered_set<std::string> getAllControlPatterns() override {
        std::unordered_set<std::string> patterns;
        for (auto const& [statementNumber, pattern] : controlPatterns) {
            patterns.insert(pattern);
        }
        return patterns;
    };

    void addControlPattern(int statementNumber, const std::string& controlPattern) override {
        controlPatterns[statementNumber] = controlPattern;
    };

    void clear() override {
        controlPatterns.clear();
    }
};