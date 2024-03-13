#include "sp/DesignExtractor/Extractor/PatternExtractor/WhilePatternExtractor.h"

WhilePatternExtractor::WhilePatternExtractor(
	std::shared_ptr<ASTNode> root,
	std::shared_ptr<ASTNode> variable,
	std::shared_ptr<WhilePatternWriter> whileWriter)
	: IPatternExtractor(root, variable, variable) {
	this->whileWriter = whileWriter;
}

void WhilePatternExtractor::extract() {
	this->whileWriter->addWhileControlVariable(this->root->getLineNumber(), this->firstClause->getValue());
}