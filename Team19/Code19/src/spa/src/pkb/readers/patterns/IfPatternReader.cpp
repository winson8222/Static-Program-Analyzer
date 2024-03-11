#include "IfPatternReader.h"

// ai-gen start(copilot, 1, e)
// prompt: used copilot
IfPatternReader::IfPatternReader(std::shared_ptr<IfPatternStore> store) : ifPatternStore(std::move(store)) {}

std::unordered_set<int> IfPatternReader::getStatementNumbersOfIfControlVariable(const std::string& controlVariable) {
	return ifPatternStore->getStatementNumbersWithIfPattern(controlVariable);
};

std::unordered_set<std::string> IfPatternReader::getControlVariablesOfIfStatement(int statementNumber) {
	return ifPatternStore->getIfPatternsWithStatementNumber(statementNumber);
};

bool IfPatternReader::hasStatementNumberWithIfPattern(int statementNumber) {
	return ifPatternStore->hasStatementNumberWithIfPattern(statementNumber);
};

std::unordered_set<int> IfPatternReader::getAllStatementNumbersOfIfControlVariables() {
	return ifPatternStore->getAllStatementNumbers();
};

std::unordered_set<std::string> IfPatternReader::getAllIfControlVariables() {
	return ifPatternStore->getAllIfPatterns();
};

// Inherited methods
bool IfPatternReader::isEmpty() {
	return ifPatternStore->isEmpty();
};

std::unordered_set<int> IfPatternReader::getAllStatementNumbers() {
	return ifPatternStore->getAllStatementNumbers();
};

std::unordered_set<std::string> IfPatternReader::getControlPatternsWithStatementNumber(int statementNumber) {
	return ifPatternStore->getIfPatternsWithStatementNumber(statementNumber);
};

std::unordered_set<int> IfPatternReader::getStatementNumbersWithControlPattern(const std::string& controlPattern) {
	return ifPatternStore->getStatementNumbersWithIfPattern(controlPattern);
};

bool IfPatternReader::hasStatementNumber(int statementNumber) {
	return ifPatternStore->hasStatementNumberWithIfPattern(statementNumber);
};

bool IfPatternReader::hasControlPattern(const std::string& controlPattern) {
	return ifPatternStore->hasIfPattern(controlPattern);
};


bool IfPatternReader::hasControlPatternAtStatement(int statementNumber, const std::string& controlPattern) {
	return ifPatternStore->hasIfPatternAtStatement(statementNumber, controlPattern);
};

std::unordered_set<std::string> IfPatternReader::getAllControlPatterns() {
	return ifPatternStore->getAllIfPatterns();
};
// ai-gen end
