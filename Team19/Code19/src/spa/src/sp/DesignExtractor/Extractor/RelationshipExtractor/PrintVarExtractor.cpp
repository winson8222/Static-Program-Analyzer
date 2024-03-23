#include "sp/DesignExtractor/Extractor/RelationshipExtractor/PrintVarExtractor.h"

PrintVarExtractor::PrintVarExtractor(std::shared_ptr<ASTNode> ast1,
	std::shared_ptr<ASTNode> ast2,
	std::shared_ptr<PrintVarNameWriter> printVarWriter)
	: IRelationshipExtractor(ast1, ast2), printVarWriter(printVarWriter) {
	this->printVarWriter = printVarWriter;
}

void PrintVarExtractor::extract() {
	this->printVarWriter->addPrintVarName(this->ast1->getLineNumber(), this->ast2->getValue());
}