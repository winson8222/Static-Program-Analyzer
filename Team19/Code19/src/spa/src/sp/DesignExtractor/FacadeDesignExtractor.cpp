#include "FacadeDesignExtractor.h"

void FDesignExtractor::extractAll() {
	if (root->type != ASTNodeType::PROGRAMS) {
		throw std::runtime_error("ERROR: This is not the start node!");
	}

	for (auto& procs : root->children) {
		if (procs->type != ASTNodeType::PROCEDURE) {
			throw std::runtime_error("ERROR: This is not a procedure node!");
		}
		ProcedureVisitor procedureVisitor(procs, pkbWriterManager);
		procedureVisitor.visit();
	}
}