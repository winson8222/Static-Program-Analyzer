#include "WhilePatternWriter.h"

WhilePatternWriter::WhilePatternWriter(std::shared_ptr<WhilePatternStore> store) : whilePatternStore(std::move(store)) {}

void WhilePatternWriter::addWhileControlVariable(int statementNumber, const std::string& whileControlVariable) {
	whilePatternStore->addWhilePattern(statementNumber, whileControlVariable);
}

void WhilePatternWriter::clear() {
	whilePatternStore->clear();
}

void WhilePatternWriter::addControlPattern(int statementNumber, const std::string& controlPattern) {
	addWhileControlVariable(statementNumber, controlPattern);
}