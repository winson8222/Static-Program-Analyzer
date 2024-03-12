#include "sp/DesignExtractor/Extractor/PatternExtractor/WhilePatternExtractor.h"

WhilePatternExtractor::WhilePatternExtractor(
	std::shared_ptr<ASTNode> root,
	std::shared_ptr<ASTNode> left,
	std::shared_ptr<ASTNode> right,
	std::shared_ptr<WhilePatternWriter> whileWriter)
	: IPatternExtractor(root, left, right) {
	this->whileWriter = whileWriter;
}

void WhilePatternExtractor::extract() {
	// TODO: Implement this
	this->whileWriter->addWhileControlVariable(this->root->getLineNumber(), this->firstClause->getValue());
	this->whileWriter->addControlPattern(this->root->getLineNumber(), this->secondClause->getRPNForm());
}