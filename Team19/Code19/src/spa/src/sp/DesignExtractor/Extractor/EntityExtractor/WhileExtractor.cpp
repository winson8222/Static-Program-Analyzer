#include "sp/DesignExtractor/Extractor/EntityExtractor/WhileExtractor.h"

WhileExtractor::WhileExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<WhileWriter> whileWriter)
	: IEntityExtractor(root) {
	if (!root->equalType(ASTNodeType::WHILE)) {
		throw std::invalid_argument("While Extractor: root is not of type While");
	}
	this->whileWriter = whileWriter;
}

void WhileExtractor::extract() {
	// Insert while entity into pkb
	this->whileWriter->insertWhile(this->root->getLineNumber());
}
