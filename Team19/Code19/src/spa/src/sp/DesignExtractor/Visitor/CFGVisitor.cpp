#include "sp/DesignExtractor/Visitor/CFGVIsitor.h"

CFGVisitor::CFGVisitor(std::vector<std::shared_ptr<CFGNode>> cfg,
	std::shared_ptr<PKBWriterManager> pkbWriterManager) {
	this->cfg = cfg;
	this->pkbWriterManager = pkbWriterManager;
}

void CFGVisitor::visit() {
	for (auto cfgNode : cfg) {
		visitCFGNode(cfgNode);
	}
}

void CFGVisitor::visitCFGNode(std::shared_ptr<CFGNode> cfgNode) {
	if (cfgNode->isEndOfProcedure()) {
		return;
	}
	// Extracts the next relationship for the current CFG node
	for (auto childNode : cfgNode->getChildren()) {
		NextExtractor nextExtractor(cfgNode, childNode, pkbWriterManager->getNextWriter());
		nextExtractor.extract();
		visitCFGNode(cfgNode);
	}
}