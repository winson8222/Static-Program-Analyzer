#pragma once

#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"
#include "sp/ControlFlow/SimpleControlFlow.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/NextExtractor.h"

#include <vector>
#include <memory>

class CFGVisitor {
public:
	CFGVisitor(std::vector<std::shared_ptr<CFGNode>> cfg,
		std::shared_ptr<PKBWriterManager> pkbWriterManager);

	void visit();
private:
	std::vector<std::shared_ptr<CFGNode>> cfg;
	std::shared_ptr<PKBWriterManager> pkbWriterManager;

	void visitCFGNode(std::shared_ptr<CFGNode> cfgNode);
};