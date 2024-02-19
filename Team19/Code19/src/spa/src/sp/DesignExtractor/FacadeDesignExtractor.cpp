#include "FacadeDesignExtractor.h"

void FDesignExtractor::extractAll() {
	if (root->type != ASTNodeType::PROGRAMS) {
		throw std::runtime_error("Not start node!");
	}

	auto program = root->children[0];

	for (auto& child : program->children) {
		if (child->type != ASTNodeType::PROCEDURE) {
			throw std::runtime_error("Not procedure node!");
		}
		ProcedureVisitor procedureVisitor(child, pkbWriterManager);
		procedureVisitor.visit();
	}
}