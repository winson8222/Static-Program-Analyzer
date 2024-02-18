#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

class ParentExtractor : public IExtractor {
public:
	explicit ParentExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};