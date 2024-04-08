#include "sp/DesignExtractor/Visitor/CFGVisitor.h"
#include <stack>

CFGVisitor::CFGVisitor(std::shared_ptr<CFGNode> cfg,
	std::shared_ptr<PKBWriterManager> pkbWriterManager) :
		cfg(cfg), pkbWriterManager(pkbWriterManager) {
}

void CFGVisitor::visit() {
	visitCFGNode(cfg);
}

void CFGVisitor::visitCFGNode(std::shared_ptr<CFGNode> cfgNode) {
	if (cfgNode->isEndOfProcedure()) {
		return;
	}

	// Extracts the next relationship for the current CFG node
	for (std::shared_ptr<CFGNode> childNode : cfgNode->getChildren()) {
		// Do not invoke the NextExtractor if the child node is a dummy node
		if (childNode->isEndOfProcedure()) {	
			continue;
		}
		// The pair of previous node to next node
		std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>> targetPair = std::make_pair(cfgNode, childNode);
		if (visited.find(targetPair) != visited.end()) {
			continue;
		}

		NextExtractor nextExtractor(cfgNode, childNode, pkbWriterManager->getNextWriter());
		nextExtractor.extract();

		// Make sure the same pair is not inserted or considered twice, to avoid call stack error
		visited.insert(targetPair);
		// Recursively visit the child node
		visitCFGNode(childNode);
	}
}
