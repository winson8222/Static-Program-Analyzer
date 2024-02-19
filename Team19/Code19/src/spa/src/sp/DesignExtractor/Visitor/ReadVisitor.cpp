#include "sp/DesignExtractor/Visitor/ReadVisitor.h"

void ReadVisitor::visit(std::shared_ptr<ASTNode> node) {
	// std::string readVar = node.getReadVar();
	// pkbWriterManager->insertReadStmt(node.getStatementNumber(), readVar);
}

void ReadVisitor::visit() {
	ReadExtractor readExtractor(this->root, this->pkbWriterManager);
	readExtractor.extract();

	VariableExtractor variableExtractor(this->root->children[0], this->pkbWriterManager);
	variableExtractor.extract();
}