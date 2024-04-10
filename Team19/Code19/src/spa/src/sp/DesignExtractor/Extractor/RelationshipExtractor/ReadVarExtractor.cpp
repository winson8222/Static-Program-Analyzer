#include "sp/DesignExtractor/Extractor/RelationshipExtractor/ReadVarExtractor.h"

ReadVarExtractor::ReadVarExtractor(std::shared_ptr<ReadVarNameWriter> readVarWriter)
	: IRelationshipExtractor(), readVarWriter(readVarWriter) {
	this->readVarWriter = readVarWriter;
}

void ReadVarExtractor::extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	this->readVarWriter->addReadVarName(ast1->getLineNumber(), ast2->getValue());
}
