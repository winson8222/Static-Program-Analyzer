#include "sp/DesignExtractor/Extractor/EntityExtractor/StatementExtractor.h"

StatementExtractor::StatementExtractor(std::shared_ptr<ASTNode> root, std::shared_ptr<StatementWriter> statementWriter)
	: IEntityExtractor(root) {
	this->statementWriter = statementWriter;
}

void StatementExtractor::extract() {
	// Insert while as a statement into pkb
	this->statementWriter->insertStatement(this->root->getLineNumber());
}
