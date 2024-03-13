#include "sp/DesignExtractor/Extractor/PatternExtractor/IfsPatternExtractor.h"

IfsPatternExtractor::IfsPatternExtractor(
	std::shared_ptr<ASTNode> root,
	std::shared_ptr<ASTNode> variable,
	std::shared_ptr<IfPatternWriter> ifWriter)
	: IPatternExtractor(root, variable, variable) {
	this->ifWriter = ifWriter;
}

void IfsPatternExtractor::extract() {
	ifWriter->addIfControlVariable(root->getLineNumber(), firstClause->getValue());
}