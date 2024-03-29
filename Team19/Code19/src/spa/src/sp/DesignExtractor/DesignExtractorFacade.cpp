#include "DesignExtractorFacade.h"

// error thrown if pkbWriterManager is null
DesignExtractorFacade::DesignExtractorFacade(std::shared_ptr<ASTNode> root, 
		std::shared_ptr<PKBWriterManager> pkbWriterManager) : root(root), pkbWriterManager(pkbWriterManager) {
	if (pkbWriterManager == nullptr) {
		throw std::runtime_error("ERROR: PKBWriterManager is null!");
	}
	if (!root->equalType(ASTNodeType::PROGRAMS)) {
		throw std::runtime_error("ERROR: This is not the start node!");
	}

	SimpleControlFlow cfg(root);
	this->cfgGraphs = *(cfg.createControlFlowGraphs());
}

// error thrown if root is not a program node or if any of the children of root is not a procedure node
// this error is expected from the requirements of SPA
void DesignExtractorFacade::extractAll() {
	for (auto& procs : root->getChildren()) {
		if (!procs->equalType(ASTNodeType::PROCEDURE)) {
			throw std::runtime_error("ERROR: This is not a procedure node!");
		}	
		handleProcedureVisitor(procs);
	}

	for (auto cfg : this->cfgGraphs) {
		handleCFGVisitor(cfg);
	}
}

void DesignExtractorFacade::handleProcedureVisitor(std::shared_ptr<ASTNode> procedureNode) {
	ProcedureVisitor procedureVisitor(procedureNode, pkbWriterManager);
	procedureVisitor.visit();
	procedureVisitor.setIsVisited();
}

void DesignExtractorFacade::handleCFGVisitor(std::shared_ptr<CFGNode> cfgNode) {
	CFGVisitor cfgVisitor(cfgNode, pkbWriterManager);
	cfgVisitor.visit();
}
