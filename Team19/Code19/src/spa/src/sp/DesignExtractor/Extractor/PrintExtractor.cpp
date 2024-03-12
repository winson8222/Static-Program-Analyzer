#include "sp/DesignExtractor/Extractor/PrintExtractor.h"

PrintExtractor::PrintExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<PrintWriter> printWriter)
	: IExtractor(root) {
	if (!root->equalType(ASTNodeType::PRINT)) {
		throw std::invalid_argument("PrintExtractor - input root is not of type print");
	}
	this->printWriter = printWriter;
}

void PrintExtractor::extract() {
	// Insert print statement into PKB
	this->printWriter->insertPrint(this->root->getLineNumber());
}