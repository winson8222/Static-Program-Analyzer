#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

class FollowsExtractor : public IExtractor {
public:
	explicit FollowsExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};