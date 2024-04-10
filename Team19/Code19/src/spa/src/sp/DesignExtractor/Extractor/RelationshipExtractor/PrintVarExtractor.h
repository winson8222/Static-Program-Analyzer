#pragma once

#include "sp/DesignExtractor/Extractor/RelationshipExtractor/IRelationshipExtractor.h"

class PrintVarExtractor : public IRelationshipExtractor {
public:
	PrintVarExtractor(std::shared_ptr<PrintVarNameWriter> printVarWriter);

	void extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) override;

private:
	std::shared_ptr<PrintVarNameWriter> printVarWriter;
};
