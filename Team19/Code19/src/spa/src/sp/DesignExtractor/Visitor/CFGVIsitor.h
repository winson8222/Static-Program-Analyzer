#pragma once

#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"
#include "sp/ControlFlow/SimpleControlFlow.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/NextExtractor.h"

#include <vector>
#include <memory>

/*
* A visitor class to visit the CFG and extract the necessary information
* This class does not implement the Visitor interface, that said
* it is a part of the visitor pattern and invoke the NextExtractor
* This is the only class that uses CFGNode from Control Flow
*/
class CFGVisitor {
public:
	/*
	* Constructor for CFGVisitor
	*/
	CFGVisitor(std::vector<std::shared_ptr<CFGNode>> cfg,
		std::shared_ptr<PKBWriterManager> pkbWriterManager);

	/*
	* Visit the CFG and extract the necessary information
	* by invoking the NextExtractor of the parent CFGNode
	* on every of its children
	*/
	void visit();

private:
	std::vector<std::shared_ptr<CFGNode>> cfg;
	std::shared_ptr<PKBWriterManager> pkbWriterManager;

	/*
	* Visit the CFGNode and extract the necessary information
	* by invoking the NextExtractor of the parent CFGNode
	* This is the supporting method to conduct depth first
	* search on the CFG. It terminates when the children of
	* the current node is a dummy node
	* @param cfgNode the CFGNode to visit
	*/
	void visitCFGNode(std::shared_ptr<CFGNode> cfgNode);
};