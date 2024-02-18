#include "FacadeDesignExtractor.h"

void FDesignExtractor::extractAll() {
	if (root->type != ASTNodeType::PROGRAMS) {
		throw std::runtime_error("Not start node!");
	}
}