#pragma once

#include "sp/AST/ASTNode.h"

class SimpleCallLinker {
public: 
	static void linkAllCallsToProcedure(std::shared_ptr<ASTNode> root);
};
