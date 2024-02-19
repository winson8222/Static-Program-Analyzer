#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

class IfThenElseExtractor : public IExtractor {
public:
	explicit IfThenElseExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};