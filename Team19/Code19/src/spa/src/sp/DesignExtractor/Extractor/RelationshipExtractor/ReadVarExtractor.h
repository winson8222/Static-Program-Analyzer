#pragma once

#include "sp/DesignExtractor/Extractor/RelationshipExtractor/IRelationshipExtractor.h"

class ReadVarExtractor : public IRelationshipExtractor {
public:
	ReadVarExtractor(std::shared_ptr<ReadVarNameWriter> readVarWriter);

	void extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) override;

private:
	std::shared_ptr<ReadVarNameWriter> readVarWriter;
};
