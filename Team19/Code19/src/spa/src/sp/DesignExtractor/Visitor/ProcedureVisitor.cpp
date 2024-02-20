#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"

void ProcedureVisitor::visit() {
	ProcedureExtractor extractor(this->root, this->pkbWriterManager);
	extractor.extract();
	// extract information of the procedure nodes: Done
	if (this->root->children.size() == 0) {
		return;
	}
	// TODO: Recursively visit the statement list node, then later recursively visit all statements
	if (this->root->children[0]->type != ASTNodeType::STATEMENT_LIST) {
		throw std::runtime_error("Procedure node does not have a statement list node");
	}
	if (this->root->children.size() != 1) {
		throw std::runtime_error("Procedure node has more than 1 child");
	}
	StatementListVisitor statementListVisitor(this->root->children[0], this->pkbWriterManager);
	statementListVisitor.visit();
}
