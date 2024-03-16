#include "sp/DesignExtractor/Extractor/EntityExtractor/CallExtractor.h"

CallExtractor::CallExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<CallWriter> callWriter)
	: IEntityExtractor(root) {
	this->callWriter = callWriter;
}

void CallExtractor::extract() {
	// Extract all the call statements
	this->callWriter->insertCall(this->root->getLineNumber());
}
