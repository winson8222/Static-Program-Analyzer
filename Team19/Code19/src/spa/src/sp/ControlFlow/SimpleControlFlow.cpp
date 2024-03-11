#include "SimpleControlFlow.h"

SimpleControlFlow::SimpleControlFlow(std::shared_ptr<ASTNode> root) : root(root) {}

std::shared_ptr<CFGNode> SimpleControlFlow::createControlFlowGraph() {
	return std::make_shared<CFGNode>();
};
