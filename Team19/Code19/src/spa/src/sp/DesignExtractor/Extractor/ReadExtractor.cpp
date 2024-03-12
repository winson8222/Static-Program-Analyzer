#include "sp/DesignExtractor/Extractor/ReadExtractor.h"

ReadExtractor::ReadExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<ReadWriter> readWriter)
	: IExtractor(root) {
	if (!root->equalType(ASTNodeType::READ)) {
		throw std::invalid_argument("ReadExtractor - input root is not of type READ");
	}
	this->readWriter = readWriter;
}

void ReadExtractor::extract() {
	// Insert read into PKB
	this->readWriter->insertRead(this->root->getLineNumber());
}