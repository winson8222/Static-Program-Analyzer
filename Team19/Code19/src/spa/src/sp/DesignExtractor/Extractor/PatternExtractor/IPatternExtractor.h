#pragma once

#include <memory>
#include "sp/AST/ASTNode.h"
#include "pkb/PKBWriterManager.h"

/*
* IRelationshipExtractor is an interface for all relationship extractors, specifically
* for traversal to expressions instead
* It is used to extract relationships from the AST and store it in the PKB
*/
class IPatternExtractor {
public:
	explicit IPatternExtractor(std::shared_ptr<ASTNode> root,
		std::shared_ptr<ASTNode> firstClause, std::shared_ptr<ASTNode> secondClause)
		: root(root), firstClause(firstClause), secondClause(secondClause) {}

	/*
	* Extracts relationships from the AST and stores it in the PKB by calling
	* the respective PKB writer manager methods
	*/
	virtual void extract() = 0;

	std::shared_ptr<ASTNode> root;
	std::shared_ptr<ASTNode> firstClause;
	std::shared_ptr<ASTNode> secondClause;
};