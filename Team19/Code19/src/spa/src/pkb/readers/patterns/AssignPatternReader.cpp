#include "AssignPatternReader.h"

// ai-gen start(copilot, 2, e)
// prompt: used copilot
AssignPatternReader::AssignPatternReader(std::shared_ptr<AssignPatternStore> store) : assignPatternStore(std::move(store)) {}

bool AssignPatternReader::isEmpty() {
  return assignPatternStore->isEmpty();
}

std::string AssignPatternReader::getLHS(int statementNumber) {
  return assignPatternStore->getLHS(statementNumber);
}

std::string AssignPatternReader::getRHS(int statementNumber) {
  return assignPatternStore->getRHS(statementNumber);
}

std::unordered_map<int, std::pair<std::string, std::string>> AssignPatternReader::getAllPatterns() {
  return assignPatternStore->getAllPatterns();
}

std::pair<std::string, std::string> AssignPatternReader::getPattern(int statementNumber) {
  return assignPatternStore->getPattern(statementNumber);
}

bool AssignPatternReader::contains(int statementNumber) {
  return assignPatternStore->contains(statementNumber);
}

std::unordered_set<int> AssignPatternReader::getAllStatementNumbers() {
  return assignPatternStore->getAllStatementNumbers();
}

std::unordered_set<int> AssignPatternReader::getStatementNumbersWithLHS(const std::string& LHS) {
  return assignPatternStore->getStatementNumbersWithLHS(LHS);
}

std::unordered_set<int> AssignPatternReader::getStatementNumbersWithRHS(const std::string& RHS) {
  return assignPatternStore->getStatementNumbersWithRHS(RHS);
}

std::unordered_set<int> AssignPatternReader::getStatementNumbersWithPartialRHS(const std::string& partialRHS) {
  return assignPatternStore->getStatementNumbersWithPartialRHS(partialRHS);
}

std::unordered_set<int> AssignPatternReader::getStatementNumbersWithLHSRHS (const std::string& LHS, const std::string& RHS) {
  return assignPatternStore->getStatementNumbersWithLHSRHS(LHS, RHS);
}

std::unordered_set<int> AssignPatternReader::getStatementNumbersWithLHSPartialRHS (const std::string& LHS, const std::string& partialRHS) {
  return assignPatternStore->getStatementNumbersWithLHSPartialRHS(LHS, partialRHS);
}
// ai-gen end
