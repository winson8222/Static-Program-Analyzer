#include "sp/DesignExtractor/Extractor/RelationshipExtractor/PrintVarExtractor.h"

PrintVarExtractor::PrintVarExtractor(std::shared_ptr<PrintVarNameWriter> printVarWriter)
	: IRelationshipExtractor(), printVarWriter(printVarWriter) {
	this->printVarWriter = printVarWriter;
}

void PrintVarExtractor::extract(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2) {
	this->printVarWriter->addPrintVarName(ast1->getLineNumber(), ast2->getValue());
}
