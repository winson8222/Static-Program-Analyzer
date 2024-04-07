#pragma once

#include <memory>
#include "sp/AST/ASTNode.h"
#include "sp/ControlFlow/CFGNode.h"
#include "pkb/PKBWriterManager.h"

/*
* IRelationshipExtractor is an interface for all relationship extractors, specifically
* for traversal to expressions instead
* It is used to extract relationships from the AST and store it in the PKB
*/
class IRelationshipExtractor {
public:
	IRelationshipExtractor() = default;

	explicit IRelationshipExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2)
		: ast1(ast1), ast2(ast2) {}

	/*
	* Extracts relationships from the AST and stores it in the PKB by calling
	* the respective PKB writer manager methods
	*/
	virtual void extract() = 0;

	/*
	* Sets the AST nodes to be used for extracting relationships
	*/
	void setASTs(std::shared_ptr<ASTNode> ast1, std::shared_ptr<ASTNode> ast2);

	std::shared_ptr<ASTNode> ast1;
	std::shared_ptr<ASTNode> ast2;
};

/*
* ICFGExtractor is an interface for all control flow graph extractors
* It is used to extract relationships from the CFG and store it in the PKB
*/
class ICFGExtractor {
public:
	ICFGExtractor() = default;

	explicit ICFGExtractor(std::shared_ptr<CFGNode> cfg1,
		std::shared_ptr<CFGNode> cfg2)
		: cfg1(cfg1), cfg2(cfg2) {}

	/*
	* Extracts relationships from the CFG and stores it in the PKB by calling
	* the respective PKB writer manager methods
	*/
	virtual void extract() = 0;

	/*
	* Sets the CFG nodes to be used for extracting relationships
	*/
	void setCFGs(std::shared_ptr<CFGNode> cfg1, std::shared_ptr<CFGNode> cfg2);

	/*
	* The parent (previous) node of the CFG
	*/
	std::shared_ptr<CFGNode> cfg1;

	/*
	* The child (next) node of the CFG
	*/
	std::shared_ptr<CFGNode> cfg2;
};
