#pragma once

#include "sp/DesignExtractor/Extractor/IExtractor.h"

class ParentExtractor : public IRelationshipExtractor {
public:
	explicit ParentExtractor(std::shared_ptr<ASTNode> ast1, 
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<PKBWriterManager> pkbWriterManager)
		: IRelationshipExtractor(ast1, ast2, pkbWriterManager) {}

	void extract() override;
};