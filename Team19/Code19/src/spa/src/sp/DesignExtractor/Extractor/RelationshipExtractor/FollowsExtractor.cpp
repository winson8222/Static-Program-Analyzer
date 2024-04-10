#include "sp/DesignExtractor/Extractor/RelationshipExtractor/FollowsExtractor.h"

FollowsExtractor::FollowsExtractor(std::shared_ptr<FollowsWriter> followsWriter) : IRelationshipExtractor() {
	this->followsWriter = followsWriter;
}

void FollowsExtractor::extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	// Extract all the follows relationships
	this->followsWriter->addFollows(
		ast1->getLineNumber(), ast2->getLineNumber()
	);
}

FollowsTExtractor::FollowsTExtractor(std::shared_ptr<FollowsTWriter> followsTWriter) : IRelationshipExtractor() {
	this->followsTWriter = followsTWriter;
}

void FollowsTExtractor::extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	// Extract all the follows star relationships
	this->followsTWriter->addFollowsT(
		ast1->getLineNumber(), ast2->getLineNumber()
	);
}
