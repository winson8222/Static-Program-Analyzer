#include "sp/DesignExtractor/Extractor/EntityExtractor/IfElseThenExtractor.h"

IfThenElseExtractor::IfThenElseExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<IfWriter> ifWriter)
	: IEntityExtractor(root) {
	this->ifWriter = ifWriter;
}

void IfThenElseExtractor::extract() {
	// Extract if then else and insert into PKB
	this->ifWriter->insertIf(this->root->getLineNumber());
}
