#include "sp/DesignExtractor/Extractor/PatternExtractor.h"

AssignPatternExtractor::AssignPatternExtractor(
	std::shared_ptr<ASTNode> ast0, 
	std::shared_ptr<ASTNode> ast1,
	std::shared_ptr<ASTNode> ast2,
	std::shared_ptr<AssignPatternWriter> patternWriter) : 
	IRelationshipExtractor(ast1, ast2) {
	this->patternWriter = patternWriter;
	this->root = ast0;
}

void AssignPatternExtractor::extract() {
	// Extract all the assign statements
	this->patternWriter->addAssignPattern(
		this->root->getLineNumber(),
		this->ast1->getValue(),
		this->ast2->getRPNForm()
	);
}