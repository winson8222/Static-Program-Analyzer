#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"

void ProcedureVisitor::visit(std::shared_ptr<ASTNode> node) {
	// do nothing for now
	ProcedureExtractor extractor(node, pkbWriterManager);
	extractor.extract();
}

void ProcedureVisitor::visit() {
	ProcedureExtractor extractor(this->root, this->pkbWriterManager);
	extractor.extract();
	// extract information of the procedure nodes: Done

	// TODO: Recursively visit the statement list node, then later recursively visit all statements
}
