#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

class AssignExtractor : public IExtractor {
public:
	explicit AssignExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};