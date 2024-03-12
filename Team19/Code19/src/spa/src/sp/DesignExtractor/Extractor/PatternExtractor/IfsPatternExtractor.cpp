#include "sp/DesignExtractor/Extractor/PatternExtractor/IfsPatternExtractor.h"

IfsPatternExtractor::IfsPatternExtractor(
	std::shared_ptr<ASTNode> root,
	std::shared_ptr<ASTNode> left,
	std::shared_ptr<ASTNode> right,
	std::shared_ptr<IfPatternWriter> ifWriter)
	: IPatternExtractor(root, left, right) {
	this->ifWriter = ifWriter;
}

void IfsPatternExtractor::extract() {
	// TODO: Implement this
	ifWriter->addIfControlVariable(root->getLineNumber(), firstClause->getValue());
	ifWriter->addControlPattern(root->getLineNumber(), secondClause->getRPNForm());
}