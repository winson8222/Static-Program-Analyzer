#include "sp/DesignExtractor/Extractor/PatternExtractor/AssignPatternExtractor.h"

AssignPatternExtractor::AssignPatternExtractor(
	std::shared_ptr<ASTNode> root, 
	std::shared_ptr<ASTNode> lhs,
	std::shared_ptr<ASTNode> rhs,
	std::shared_ptr<AssignPatternWriter> patternWriter) : 
	IPatternExtractor(root, lhs, rhs) {
	this->patternWriter = patternWriter;
}

void AssignPatternExtractor::extract() {
	// Extract all the assign statements
	this->patternWriter->addAssignPattern(
		this->root->getLineNumber(),
		this->firstClause->getValue(),
		this->secondClause->getRPNForm()
	);
}