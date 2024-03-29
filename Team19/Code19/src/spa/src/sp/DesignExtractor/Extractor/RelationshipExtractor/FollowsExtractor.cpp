#include "sp/DesignExtractor/Extractor/RelationshipExtractor/FollowsExtractor.h"

FollowsExtractor::FollowsExtractor(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2,
	std::shared_ptr<FollowsWriter> followsWriter) : IRelationshipExtractor(ast1, ast2) {
	this->followsWriter = followsWriter;
}

void FollowsExtractor::extract() {
	// Extract all the follows relationships
	this->followsWriter->addFollows(
		this->ast1->getLineNumber(), this->ast2->getLineNumber()
	);
}

FollowsTExtractor::FollowsTExtractor(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2,
	std::shared_ptr<FollowsTWriter> followsTWriter) : IRelationshipExtractor(ast1, ast2) {
	this->followsTWriter = followsTWriter;
}

void FollowsTExtractor::extract() {
	// Extract all the follows star relationships
	this->followsTWriter->addFollowsT(
		this->ast1->getLineNumber(), this->ast2->getLineNumber()
	);
}
