#include "SimpleControlFlow.h"

SimpleControlFlow::SimpleControlFlow(std::shared_ptr<ASTNode> root) : root(root) {}

std::shared_ptr<std::vector<std::shared_ptr<CFGNode>>> SimpleControlFlow::createControlFlowGraphs() {
	std::vector<std::shared_ptr<ASTNode>> procedures = this->root->getChildren();

	std::shared_ptr<std::vector<std::shared_ptr<CFGNode>>> controlFlowGraphs = std::make_shared<std::vector<std::shared_ptr<CFGNode>>>();

	for (auto& procedure : procedures) {
		std::shared_ptr<CFGNode> procedureCfg = this->generateCfg(procedure);
	}

	return controlFlowGraphs;
};

std::shared_ptr<CFGNode> SimpleControlFlow::generateCfg(std::shared_ptr<ASTNode> procedureNode) {
	// TODO
	return std::make_shared<CFGNode>();
}
