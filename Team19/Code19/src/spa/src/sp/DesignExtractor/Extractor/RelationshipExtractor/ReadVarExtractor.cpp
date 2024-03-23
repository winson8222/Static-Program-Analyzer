#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ReadVarExtractor.h"

ReadVarExtractor::ReadVarExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2,
		std::shared_ptr<ReadVarNameWriter> readVarWriter)
	: IRelationshipExtractor(ast1, ast2), readVarWriter(readVarWriter) {
	this->readVarWriter = readVarWriter;
}

void ReadVarExtractor::extract() {
	this->readVarWriter->addReadVarName(this->ast1->getLineNumber(), this->ast2->getValue());
}