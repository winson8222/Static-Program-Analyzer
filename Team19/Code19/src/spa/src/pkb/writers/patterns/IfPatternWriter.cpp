#include "IfPatternWriter.h"

IfPatternWriter::IfPatternWriter(std::shared_ptr<IfPatternStore> store) : ifPatternStore(std::move(store)) {}

void IfPatternWriter::addIfControlVariable(int statementNumber, const std::string& ifControlVariable) {
	ifPatternStore->addIfPattern(statementNumber, ifControlVariable);
}

void IfPatternWriter::clear() {
	ifPatternStore->clear();
}

void IfPatternWriter::addControlPattern(int statementNumber, const std::string& controlPattern) {
	addIfControlVariable(statementNumber, controlPattern);
}