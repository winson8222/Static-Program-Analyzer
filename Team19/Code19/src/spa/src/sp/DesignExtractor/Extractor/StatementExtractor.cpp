#include "sp/DesignExtractor/Extractor/StatementExtractor.h"

StatementExtractor::StatementExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<StatementWriter> statementWriter)
	: IExtractor(root) {
	this->statementWriter = statementWriter;
}

void StatementExtractor::extract() {
	// Insert while as a statement into pkb
	this->statementWriter->insertStatement(this->root->getLineNumber());
}