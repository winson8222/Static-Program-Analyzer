#pragma once

#include <memory>
#include "sp/AST/ASTNode.h"
#include "pkb/PKBWriterManager.h"

/*
* IRelationshipExtractor is an interface for all relationship extractors, specifically
* for traversal to expressions instead
* It is used to extract relationships from the AST and store it in the PKB
*/
class IRelationshipExtractor {
public:
	explicit IRelationshipExtractor(std::shared_ptr<ASTNode> ast1,
		std::shared_ptr<ASTNode> ast2)
		: ast1(ast1), ast2(ast2) {}

	/*
	* Extracts relationships from the AST and stores it in the PKB by calling
	* the respective PKB writer manager methods
	*/
	virtual void extract() = 0;

	std::shared_ptr<ASTNode> ast1;
	std::shared_ptr<ASTNode> ast2;
};