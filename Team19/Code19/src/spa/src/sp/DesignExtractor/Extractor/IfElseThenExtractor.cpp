#include "sp/DesignExtractor/Extractor/IfElseThenExtractor.h"

IfThenElseExtractor::IfThenElseExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<IfWriter> ifWriter)
	: IExtractor(root) {
	this->ifWriter = ifWriter;
}

void IfThenElseExtractor::extract() {
	// Extract if then else and insert into PKB
	this->ifWriter->insertIf(this->root->getLineNumber());
}