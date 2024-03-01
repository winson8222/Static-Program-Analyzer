#include "WhilePatternReader.h"

// ai-gen start(copilot, 0, e)
// prompt: used copilot
WhilePatternReader::WhilePatternReader(std::shared_ptr<WhilePatternStore> store) : whilePatternStore(std::move(store)) {}

std::unordered_set<int> WhilePatternReader::getStatementNumbersOfWhileControlVariable(const std::string& controlVariable) {
	return whilePatternStore->getStatementNumbersWithWhilePattern(controlVariable);
};

std::unordered_set<std::string> WhilePatternReader::getControlVariablesOfWhileStatement(int statementNumber) {
	return whilePatternStore->getWhilePatternsWithStatementNumber(statementNumber);
};

bool WhilePatternReader::hasStatementNumberWithWhilePattern(int statementNumber) {
	return whilePatternStore->hasStatementNumberWithWhilePattern(statementNumber);
};

std::unordered_set<int> WhilePatternReader::getAllStatementNumbersOfWhileControlVariables() {
	return whilePatternStore->getAllStatementNumbers();
};

std::unordered_set<std::string> WhilePatternReader::getAllWhileControlVariables() {
	return whilePatternStore->getAllWhilePatterns();
};

// Inherited methods
bool WhilePatternReader::isEmpty() {
	return whilePatternStore->isEmpty();
};

std::unordered_set<int> WhilePatternReader::getAllStatementNumbers() {
	return whilePatternStore->getAllStatementNumbers();
};

std::unordered_set<std::string> WhilePatternReader::getControlPatternsWithStatementNumber(int statementNumber) {
	return whilePatternStore->getWhilePatternsWithStatementNumber(statementNumber);
};

std::unordered_set<int> WhilePatternReader::getStatementNumbersWithControlPattern(const std::string& controlPattern) {
	return whilePatternStore->getStatementNumbersWithWhilePattern(controlPattern);
};

bool WhilePatternReader::hasStatementNumber(int statementNumber) {
	return whilePatternStore->hasStatementNumberWithWhilePattern(statementNumber);
};

bool WhilePatternReader::hasControlPattern(const std::string& controlPattern) {
	return whilePatternStore->hasWhilePattern(controlPattern);
};


bool WhilePatternReader::hasControlPatternAtStatement(int statementNumber, const std::string& controlPattern) {
	return whilePatternStore->hasWhilePatternAtStatement(statementNumber, controlPattern);
};

std::unordered_set<std::string> WhilePatternReader::getAllControlPatterns() {
	return whilePatternStore->getAllWhilePatterns();
};
// ai-gen end
