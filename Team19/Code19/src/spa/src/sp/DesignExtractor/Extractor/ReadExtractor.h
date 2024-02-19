#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"
#include <iostream>

class ReadExtractor : public IExtractor {
public:
	explicit ReadExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};