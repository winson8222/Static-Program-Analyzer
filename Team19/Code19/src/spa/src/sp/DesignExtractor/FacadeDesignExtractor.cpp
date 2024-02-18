#include "FacadeDesignExtractor.h"

void FDesignExtractor::extractAll() {
	if (root->type != ASTNodeType::PROGRAMS) {
		throw std::runtime_error("Not start node!");
	}

	for (auto& child : root->children) {
		if (child->type != ASTNodeType::PROCEDURE) {
			throw std::runtime_error("Syntax error!");
			ProcedureVisitor procedureVisitor(child, pkbWriterManager);
			procedureVisitor.visit(*static_cast<ProcedureNode*>(child.get())); // Assuming dynamic polymorphism
		}
	}
}