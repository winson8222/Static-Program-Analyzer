#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"


class WhileExtractor : public IExtractor {
public:
	explicit WhileExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};