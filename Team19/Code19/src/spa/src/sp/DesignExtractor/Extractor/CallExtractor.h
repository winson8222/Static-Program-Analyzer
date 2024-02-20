#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

class CallExtractor : public IExtractor {
public:
	explicit CallExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};