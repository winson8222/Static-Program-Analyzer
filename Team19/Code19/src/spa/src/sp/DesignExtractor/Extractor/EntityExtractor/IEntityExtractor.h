#pragma once

#include <memory>
#include "sp/AST/ASTNode.h"
#include "pkb/PKBWriterManager.h"

/*
* IExtractor is an interface for all extractors (specifically for entities)
* It is used to extract entity designs from the AST and store it in the PKB
*/
class IEntityExtractor {
public:
	/*
	* Constructor for IExtractor, takes in the root of the AST and the PKBWriterManager
	*/
	explicit IEntityExtractor(std::shared_ptr<ASTNode> root)
		: root(root) {}

	/*
	* Extracts information from the AST and stores it in the PKB by calling
	* the respective PKB writer manager methods
	*/
	virtual void extract() = 0;

	std::shared_ptr<ASTNode> root;
};