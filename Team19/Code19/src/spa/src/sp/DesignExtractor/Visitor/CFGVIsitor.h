#pragma once

#include "sp/DesignExtractor/Visitor/ProcedureVisitor.h"
#include "sp/ControlFlow/SimpleControlFlow.h"
#include "sp/DesignExtractor/Extractor/RelationshipExtractor/NextExtractor.h"

#include <vector>
#include <memory>

// ai-gen start(copilot, 2, e)

/*
* The Structure that represents hash value of a pair
* of CFGNode
*/
struct PairHash {
	template <class T1, class T2>
	std::size_t operator () (const std::pair<T1, T2>& pair) const {
		auto hash1 = std::hash<T1>()(pair.first);
		auto hash2 = std::hash<T2>()(pair.second);
		// Combine the two hash values. This is a simple way to do it.
		return hash1 ^ (hash2 << 1);
	}
};

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
	CFGVisitor(std::shared_ptr<CFGNode> cfg,
		std::shared_ptr<PKBWriterManager> pkbWriterManager);

	/*
	* Visit the CFG and extract the necessary information
	* by invoking the NextExtractor of the parent CFGNode
	* on every of its children
	*/
	void visit();

private:
	std::shared_ptr<CFGNode> cfg;
	std::shared_ptr<PKBWriterManager> pkbWriterManager;

	/*
	* A set to keep track of visited pairs of CFGNode, takes in
	* a pair of <Previous Node, Next Node>
	*/
	std::unordered_set<std::pair<std::shared_ptr<CFGNode>, std::shared_ptr<CFGNode>>, PairHash> visited;

	/*
	* Visit the CFGNode and extract the necessary information
	* by invoking the NextExtractor of the parent CFGNode
	* This is the supporting method to conduct depth first
	* search on the CFG. It terminates when the children of
	* the current node is a dummy node
	* 
	* @param cfgNode the CFGNode to visit
	*/
	void visitCFGNode(std::shared_ptr<CFGNode> cfgNode);
};

// ai-gen end