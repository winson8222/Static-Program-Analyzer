#pragma once

#include <unordered_map>
#include <unordered_set>
#include <utility>
#include "pkb/templates/TemplateMapSet.h"
#include "string"
#include "IAssignPatternReader.h"
#include "IAssignPatternWriter.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
/**
 * @brief A store for managing assign patterns.
 */
class AssignPatternStore : public IAssignPatternReader, public IAssignPatternWriter {
private:
    std::unordered_map<int, std::string> LHSMap;
    std::unordered_map<int, std::string> RHSMap;
public:
    // Adds an assign pattern to the store.
    void addAssignPattern(int statementNumber, std::string LHS, std::string RHS) override {
        LHSMap[statementNumber] = std::move(LHS);
        RHSMap[statementNumber] = std::move(RHS);
    }

    // Clears all assign patterns from the store.
    void clear() override {
        LHSMap.clear();
        RHSMap.clear();
    }

    // Checks if the store is empty.
    bool isEmpty() override {
        return LHSMap.empty() && RHSMap.empty();
    }

    // Retrieves the assign pattern for a given statement number.
    std::pair<std::string, std::string> getPattern(int statementNumber) override {
        return std::make_pair(LHSMap[statementNumber], RHSMap[statementNumber]);
    }

    // Retrieves all assign patterns from the store.
    std::unordered_map<int, std::pair<std::string, std::string>> getAllPatterns() override {
        std::unordered_map<int, std::pair<std::string, std::string>> result;
        for (auto const& [key, value] : LHSMap) {
            result[key] = std::make_pair(value, RHSMap.at(key));
        }
        return result;
    }

    // Get LHS of the assign pattern for a given statement number.
    std::string getLHS(int statementNumber) override {
        return LHSMap.at(statementNumber);
    }

    // Get RHS of the assign pattern for a given statement number.
    std::string getRHS(int statementNumber) override {
        return RHSMap.at(statementNumber);
    }

    // Checks if the store contains a given assign pattern.
    bool contains(int statementNumber) override {
        return LHSMap.find(statementNumber) != LHSMap.end();
    }

    // Retrieves all statement numbers from the store.
    std::unordered_set<int> getAllStatementNumbers() override {
        std::unordered_set<int> result;
        for (auto const& [key, value] : LHSMap) {
            result.insert(key);
        }
        return result;
    }

    // Checks if the store contains a LHS and returns the set of statement numbers that contain the LHS.
    std::unordered_set<int> getStatementNumbersWithLHS(const std::string& LHS) override {
        std::unordered_set<int> result;
        for (auto const& [key, value] : LHSMap) {
            if (value == LHS) {
                result.insert(key);
            }
        }
        return result;
    }

    // Checks if the store contains a RHS and returns the set of statement numbers that contain the RHS.
    std::unordered_set<int> getStatementNumbersWithRHS(const std::string& RHS) override {
        std::unordered_set<int> result;
        for (auto const& [key, value] : RHSMap) {
            if (value == RHS) {
                result.insert(key);
            }
        }
        return result;
    }

    // Checks if the store contains a partial RHS and returns the set of statement numbers that contain the partial RHS.
    std::unordered_set<int> getStatementNumbersWithPartialRHS(const std::string& RHS) override {
        std::unordered_set<int> result;
        for (auto const& [key, value] : RHSMap) {
            if (value.find(RHS) != std::string::npos) {
                result.insert(key);
            }
        }
        return result;
    }

    // Checks if the store contains a LHS and RHS and returns the set of statement numbers that contain the LHS and RHS.
    std::unordered_set<int> getStatementNumbersWithLHSRHS(const std::string&LHS, const std::string& RHS) override {
        std::unordered_set<int> result;
        for (auto const& [key, value] : LHSMap) {
            if (value == LHS && RHSMap.at(key) == RHS) {
                result.insert(key);
            }
        }
        return result;
    }

    // Checks if the store contains a LHS and a partial RHS and returns the set of statement numbers that contain the LHS and partial RHS.
    std::unordered_set<int> getStatementNumbersWithLHSPartialRHS(const std::string& LHS, const std::string& RHS) override {
        std::unordered_set<int> result;
        for (auto const& [key, value] : LHSMap) {
            if (value == LHS && RHSMap.at(key).find(RHS) != std::string::npos) {
                result.insert(key);
            }
        }
        return result;
    }
};
// ai-gen end
