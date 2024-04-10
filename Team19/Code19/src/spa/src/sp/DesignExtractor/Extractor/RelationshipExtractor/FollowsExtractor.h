#pragma once

#include "sp/DesignExtractor/Extractor/RelationshipExtractor/IRelationshipExtractor.h"

class FollowsExtractor : public IRelationshipExtractor {
public:
	FollowsExtractor(std::shared_ptr<FollowsWriter> followsWriter);

	void extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) override;

private:
	std::shared_ptr<FollowsWriter> followsWriter;
};

class FollowsTExtractor : public IRelationshipExtractor {
public:
	FollowsTExtractor(std::shared_ptr<FollowsTWriter> followsTWriter);

	void extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) override;
private:
	std::shared_ptr<FollowsTWriter> followsTWriter;
};
