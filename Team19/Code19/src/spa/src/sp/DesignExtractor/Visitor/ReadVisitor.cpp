#include "sp/DesignExtractor/Visitor/ReadVisitor.h"

void ReadVisitor::visit(std::shared_ptr<ASTNode> node) {
	// std::string readVar = node.getReadVar();
	// pkbWriterManager->insertReadStmt(node.getStatementNumber(), readVar);
}

void ReadVisitor::visit() {
	// TODO
}