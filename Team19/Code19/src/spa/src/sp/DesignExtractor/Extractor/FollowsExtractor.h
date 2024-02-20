#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

class FollowsExtractor : public IRelationshipExtractor {
public:
	FollowsExtractor(std::shared_ptr<ASTNode> ast1, 
		std::shared_ptr<ASTNode> ast2, 
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IRelationshipExtractor(ast1, ast2, pkbWriterManager) {}

	void extract() override;
};