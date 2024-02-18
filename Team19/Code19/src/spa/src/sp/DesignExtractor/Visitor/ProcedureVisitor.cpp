#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"

void ProcedureVisitor::visit(std::shared_ptr<ASTNode> node) {
	// do nothing for now
	ProcedureExtractor extractor(node, pkbWriterManager);
	extractor.extract();
}