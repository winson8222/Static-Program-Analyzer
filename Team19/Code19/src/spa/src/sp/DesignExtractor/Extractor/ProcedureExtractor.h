#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

class ProcedureExtractor : public IExtractor {
public:
	explicit ProcedureExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IExtractor(root, pkbWriterManager) {}

	void extract() override;
};